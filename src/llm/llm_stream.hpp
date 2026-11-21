#pragma once

// llm-stream v0.3.0, https://github.com/Mattbusel/llm-stream (MIT License)

// llm_stream.hpp — Zero-dependency single-header C++ library for streaming LLM responses.
// Supports OpenAI (Chat Completions and the Responses API) and Anthropic via libcurl
// SSE streaming.
//
// USAGE:
//   In exactly ONE .cpp file before including:
//     #define LLM_STREAM_IMPLEMENTATION
//     #include "llm_stream.hpp"
//
//   In all other files just:
//     #include "llm_stream.hpp"
//
// Requires: libcurl (ships on macOS, most Linux distros; vcpkg/apt on Windows)
// C++17 or later. Compiles with -Wall -Wextra -std=c++17.
//
// SSE PARSER ONLY:
//   llm::SseParser and llm::parse_sse() are header-only (inline) and need neither
//   libcurl nor LLM_STREAM_IMPLEMENTATION. Use them to parse text/event-stream
//   bodies fetched by your own HTTP client. Define LLM_STREAM_NO_CURL before
//   including to get only the parser, without <curl/curl.h> and the network API.

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <functional>
#include <mutex>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace llm {

// ---------------------------------------------------------------------------
// Server-Sent Events parser (header-only, standard library only)
// ---------------------------------------------------------------------------

/// One Server-Sent Events event.
struct SseEvent {
    std::string event = "message"; ///< `event:` field; "message" when the event has none
    std::string data;              ///< `data:` lines joined with '\n'
    std::string id;                ///< Last `id:` seen on the stream (it carries over, per the spec)
};

using SseCallback = std::function<void(const SseEvent& event)>;

/// Incremental parser for a `text/event-stream` body, following the WHATWG rules:
/// LF, CRLF or CR line ends (also when split across chunks), a leading UTF-8 BOM,
/// `:` comment lines, one optional space after the colon, multi-line `data:` joined
/// with '\n', events dispatched on a blank line, and events with no `data:` dropped.
/// Feed bytes in whatever chunks they arrive.
///
/// # Example
/// ```cpp
/// llm::SseParser p;
/// p.feed("event: ping\ndata: {\"a\"", on_event);
/// p.feed(":1}\n\n", on_event);   // on_event({"ping", "{\"a\":1}", ""})
/// p.finish(on_event);
/// ```
class SseParser {
public:
    /// Parse `chunk` and call `on_event` for every event it completes.
    inline void feed(std::string_view chunk, const SseCallback& on_event);
    /// End of stream: parse a last line that has no line end and dispatch a final
    /// event that has data but no blank line after it (lenient: browsers drop it).
    /// The parser is then reset for a new stream.
    inline void finish(const SseCallback& on_event);
    /// Forget all state, including the last event id and retry value.
    void reset() { *this = SseParser(); }
    /// Last valid `retry:` value in milliseconds, or -1 if none was sent.
    long retry_ms() const { return retry_ms_; }

private:
    inline void process_line(const SseCallback& on_event);
    inline void dispatch(const SseCallback& on_event);

    std::string line_;            ///< Partial line carried over between chunks
    std::string event_;           ///< Event type buffer
    std::string data_;            ///< Data buffer, each line followed by '\n'
    std::string id_;              ///< Last event id buffer
    long        retry_ms_ = -1;
    bool        skip_lf_  = false; ///< The previous chunk ended in CR: drop a leading LF
    bool        first_line_ = true; ///< Strip a UTF-8 BOM from the first line
};

/// Parse a complete SSE body and return its events (calls `SseParser::finish`).
inline std::vector<SseEvent> parse_sse(std::string_view body) {
    std::vector<SseEvent> events;
    SseParser parser;
    const SseCallback collect = [&events](const SseEvent& e) { events.push_back(e); };
    parser.feed(body, collect);
    parser.finish(collect);
    return events;
}

inline void SseParser::feed(std::string_view chunk, const SseCallback& on_event) {
    size_t i = 0;
    if (skip_lf_ && !chunk.empty()) {
        skip_lf_ = false;
        if (chunk[0] == '\n') i = 1;
    }
    while (i < chunk.size()) {
        const size_t end = chunk.find_first_of("\r\n", i);
        if (end == std::string_view::npos) {
            line_.append(chunk.data() + i, chunk.size() - i);
            return;
        }
        line_.append(chunk.data() + i, end - i);
        process_line(on_event);
        i = end + 1;
        if (chunk[end] == '\r') {
            if (i == chunk.size()) skip_lf_ = true;     // CRLF may be split across chunks
            else if (chunk[i] == '\n') ++i;
        }
    }
}

inline void SseParser::finish(const SseCallback& on_event) {
    if (!line_.empty()) process_line(on_event);
    dispatch(on_event);
    reset();
}

inline void SseParser::process_line(const SseCallback& on_event) {
    std::string line;
    line.swap(line_);
    if (first_line_) {
        first_line_ = false;
        if (line.compare(0, 3, "\xEF\xBB\xBF") == 0) line.erase(0, 3);
    }
    if (line.empty()) {
        dispatch(on_event);
        return;
    }
    if (line[0] == ':') return; // comment
    std::string_view field(line);
    std::string_view value;
    const size_t colon = field.find(':');
    if (colon != std::string_view::npos) {
        value = field.substr(colon + 1);
        field = field.substr(0, colon);
        if (!value.empty() && value[0] == ' ') value.remove_prefix(1);
    }
    if (field == "event") {
        event_.assign(value.data(), value.size());
    } else if (field == "data") {
        data_.append(value.data(), value.size());
        data_ += '\n';
    } else if (field == "id") {
        if (value.find('\0') == std::string_view::npos) id_.assign(value.data(), value.size());
    } else if (field == "retry") {
        long ms = 0;
        bool ok = !value.empty() && value.size() <= 9;
        for (char c : value) {
            if (c < '0' || c > '9') { ok = false; break; }
            ms = ms * 10 + (c - '0');
        }
        if (ok) retry_ms_ = ms;
    }
}

inline void SseParser::dispatch(const SseCallback& on_event) {
    if (data_.empty()) {
        event_.clear();
        return;
    }
    data_.pop_back(); // the '\n' after the last data line
    SseEvent ev;
    if (!event_.empty()) ev.event = std::move(event_);
    ev.data = std::move(data_);
    ev.id   = id_;
    event_.clear();
    data_.clear();
    if (on_event) on_event(ev);
}

} // namespace llm

#ifndef LLM_STREAM_NO_CURL

#include <curl/curl.h>

namespace llm {

// ---------------------------------------------------------------------------
// Public types
// ---------------------------------------------------------------------------

/// Configuration for an LLM request.
struct Config {
    std::string api_key;
    std::string model         = "gpt-4o-mini"; ///< Default model; "claude-*" prefix routes to Anthropic
    int         max_tokens    = 1024;
    double      temperature   = 0.7;
    std::string system_prompt;                 ///< Optional system/instruction prompt
};

/// Statistics surfaced at the end of a stream.
struct StreamStats {
    size_t token_count    = 0;    ///< Number of text deltas received
    double elapsed_ms     = 0.0;
    double tokens_per_sec = 0.0;  ///< Deltas per second
    long   input_tokens   = -1;   ///< Billed input tokens, when the provider reports them (-1 if not)
    long   output_tokens  = -1;   ///< Billed output tokens, when the provider reports them (-1 if not)
    std::string response_id;      ///< Responses API: the response id (pass as previous_response_id)
};

using TokenCallback = std::function<void(std::string_view token)>;
using DoneCallback  = std::function<void(const StreamStats&)>;
using ErrorCallback = std::function<void(std::string_view error)>;

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

/// Stream a response from OpenAI (chat/completions) via SSE.
///
/// # Arguments
/// * `prompt`   — User message
/// * `config`   — API key, model, generation parameters
/// * `on_token` — Invoked for every streamed token fragment
/// * `on_done`  — Invoked once when the stream ends successfully (optional)
/// * `on_error` — Invoked on network/HTTP error (optional)
///
/// # Panics
/// This function never panics.
void stream_openai(
    const std::string& prompt,
    const Config&      config,
    TokenCallback      on_token,
    DoneCallback       on_done  = nullptr,
    ErrorCallback      on_error = nullptr
);

/// Stream a response from Anthropic (messages) via SSE.
///
/// # Arguments
/// * `prompt`   — User message
/// * `config`   — API key, model, generation parameters
/// * `on_token` — Invoked for every streamed token fragment
/// * `on_done`  — Invoked once when the stream ends successfully (optional)
/// * `on_error` — Invoked on network/HTTP error (optional)
///
/// # Panics
/// This function never panics.
void stream_anthropic(
    const std::string& prompt,
    const Config&      config,
    TokenCallback      on_token,
    DoneCallback       on_done  = nullptr,
    ErrorCallback      on_error = nullptr
);

/// Stream a response from OpenAI's Responses API (`POST /v1/responses`) via SSE.
///
/// Sends `input` = the prompt, `instructions` = `config.system_prompt`,
/// `max_output_tokens` = `config.max_tokens`. `temperature` is sent except for the
/// reasoning models that reject it (`o1`, `o3`, `o4`, `gpt-5` families). Text arrives
/// from `response.output_text.delta` events; on `response.completed` the stats carry
/// the billed `input_tokens` / `output_tokens` and the `response_id`. A
/// `response.failed`, `response.incomplete` or `error` event is reported through
/// `on_error` with the API's message, and `on_done` is not called.
///
/// # Arguments
/// * `prompt`   - User input
/// * `config`   - API key, model, generation parameters
/// * `on_token` - Invoked for every streamed text fragment
/// * `on_done`  - Invoked once when the response completes (optional)
/// * `on_error` - Invoked on network, HTTP or API error (optional)
///
/// # Example
/// ```cpp
/// llm::Config cfg;
/// cfg.api_key = std::getenv("OPENAI_API_KEY");
/// cfg.model   = "gpt-4.1-mini";
/// llm::stream_openai_responses("Hello!", cfg,
///     [](std::string_view tok){ std::cout << tok; },
///     [](const llm::StreamStats& s){ std::cout << s.output_tokens << " tokens\n"; });
/// ```
///
/// # Panics
/// This function never panics.
void stream_openai_responses(
    const std::string& prompt,
    const Config&      config,
    TokenCallback      on_token,
    DoneCallback       on_done  = nullptr,
    ErrorCallback      on_error = nullptr
);

/// Auto-detect provider from model name prefix and stream.
/// Models starting with "claude-" → Anthropic; everything else → OpenAI.
///
/// # Example
/// ```cpp
/// llm::Config cfg;
/// cfg.api_key = std::getenv("OPENAI_API_KEY");
/// cfg.model   = "gpt-4o-mini";
/// llm::stream("Hello!", cfg, [](std::string_view tok){ std::cout << tok; });
/// ```
///
/// # Panics
/// This function never panics.
void stream(
    const std::string& prompt,
    const Config&      config,
    TokenCallback      on_token,
    DoneCallback       on_done  = nullptr,
    ErrorCallback      on_error = nullptr
);

} // namespace llm

// ---------------------------------------------------------------------------
// Implementation — compiled in exactly one translation unit.
// ---------------------------------------------------------------------------
#ifdef LLM_STREAM_IMPLEMENTATION

namespace llm {
namespace detail {

// ---------------------------------------------------------------------------
// Minimal hand-rolled JSON helpers. No external dependencies.
//
// json_extract_string: finds `"key": "value"` (whitespace-tolerant) in a
//   flat JSON fragment and returns the unescaped string value, or "" if absent.
//
// json_extract_nested: locates the first occurrence of `"outer"` then
//   searches for `"inner"` within the remainder — sufficient for SSE deltas
//   like {"delta":{"type":"text_delta","text":"hi"}} with outer="delta",
//   inner="text".
// ---------------------------------------------------------------------------

/// Extract value of a string key from flat JSON — sufficient for SSE deltas.
static std::string json_extract_string(std::string_view json, std::string_view key) {
    // Build search token: "key"
    std::string pattern;
    pattern.reserve(key.size() + 2);
    pattern += '"';
    pattern += key;
    pattern += '"';

    auto pos = json.find(pattern);
    if (pos == std::string_view::npos) return {};

    pos += pattern.size();
    // Skip optional whitespace and the colon
    while (pos < json.size() &&
           (json[pos] == ' ' || json[pos] == '\t' || json[pos] == ':'))
        ++pos;

    if (pos >= json.size() || json[pos] != '"') return {};
    ++pos; // skip opening quote

    std::string result;
    result.reserve(64);
    while (pos < json.size() && json[pos] != '"') {
        if (json[pos] == '\\' && pos + 1 < json.size()) {
            switch (json[pos + 1]) {
                case '"':  result += '"';  break;
                case '\\': result += '\\'; break;
                case '/':  result += '/';  break;
                case 'n':  result += '\n'; break;
                case 'r':  result += '\r'; break;
                case 't':  result += '\t'; break;
                default:   result += json[pos + 1]; break;
            }
            pos += 2;
        } else {
            result += json[pos++];
        }
    }
    return result;
}

/// Extract value of a nested key path: locate `"outer"` first, then find
/// `"inner"` within the JSON from that point onward.
static std::string json_extract_nested(std::string_view json,
                                       std::string_view outer,
                                       std::string_view inner) {
    std::string outer_pattern;
    outer_pattern.reserve(outer.size() + 2);
    outer_pattern += '"';
    outer_pattern += outer;
    outer_pattern += '"';

    auto pos = json.find(outer_pattern);
    if (pos == std::string_view::npos) return {};

    return json_extract_string(json.substr(pos), inner);
}

// ---------------------------------------------------------------------------
// RAII wrappers around libcurl types
// ---------------------------------------------------------------------------

/// Thread-safe one-time libcurl global initialization.
/// curl_global_init is not thread-safe; calling it from curl_easy_init's
/// implicit path races under concurrent stream() calls. We do it once here.
inline void curl_global_init_once() {
    static std::once_flag flag;
    std::call_once(flag, []{ curl_global_init(CURL_GLOBAL_DEFAULT); });
}

/// RAII wrapper around a CURL* easy handle.
struct CurlHandle {
    CURL* handle = nullptr;
    CurlHandle() { curl_global_init_once(); handle = curl_easy_init(); }
    ~CurlHandle() { if (handle) curl_easy_cleanup(handle); }
    CurlHandle(const CurlHandle&)            = delete;
    CurlHandle& operator=(const CurlHandle&) = delete;
    explicit operator CURL*() const { return handle; }
    bool ok() const { return handle != nullptr; }
};

/// RAII wrapper around a curl_slist* header list.
struct CurlSlist {
    curl_slist* list = nullptr;
    CurlSlist() = default;
    ~CurlSlist() { if (list) curl_slist_free_all(list); }
    CurlSlist(const CurlSlist&)            = delete;
    CurlSlist& operator=(const CurlSlist&) = delete;
    void append(const char* s) { list = curl_slist_append(list, s); }
};

// ---------------------------------------------------------------------------
// SSE streaming write-callback context
// ---------------------------------------------------------------------------
enum class Provider { OpenAI, Anthropic, OpenAIResponses };

struct StreamCtx {
    Provider      provider;
    TokenCallback on_token;
    SseParser     sse;           ///< Carries partial lines and events between curl callbacks
    size_t        token_count = 0;
    std::string   raw;           ///< First bytes of the body, for HTTP error messages
    std::string   api_error;     ///< Responses API: error message from a failure event
    bool          completed = false; ///< Responses API: response.completed was seen
    long          input_tokens  = -1;
    long          output_tokens = -1;
    std::string   response_id;
};

/// Extract the integer value of `"key": 123` (first occurrence), or -1.
static long json_extract_int(std::string_view json, std::string_view key) {
    std::string pattern = "\"" + std::string(key) + "\"";
    auto pos = json.find(pattern);
    if (pos == std::string_view::npos) return -1;
    pos += pattern.size();
    while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == ':'))
        ++pos;
    long v = 0;
    bool any = false;
    while (pos < json.size() && json[pos] >= '0' && json[pos] <= '9') {
        v = v * 10 + (json[pos] - '0');
        any = true;
        ++pos;
    }
    return any ? v : -1;
}

/// Handle one Responses API SSE event (a `data:` payload carrying its `type`).
static void responses_event(StreamCtx* ctx, std::string_view payload) {
    const std::string type = json_extract_string(payload, "type");
    if (type == "response.output_text.delta") {
        std::string token = json_extract_string(payload, "delta");
        if (!token.empty() && ctx->on_token) {
            ctx->on_token(token);
            ++ctx->token_count;
        }
    } else if (type == "response.completed") {
        ctx->completed = true;
        auto usage = payload.find("\"usage\"");
        if (usage != std::string_view::npos) {
            ctx->input_tokens  = json_extract_int(payload.substr(usage), "input_tokens");
            ctx->output_tokens = json_extract_int(payload.substr(usage), "output_tokens");
        }
        ctx->response_id = json_extract_nested(payload, "response", "id");
    } else if (type == "response.failed" || type == "error") {
        std::string msg = json_extract_nested(payload, "error", "message");
        if (msg.empty()) msg = json_extract_string(payload, "message");
        ctx->api_error = msg.empty() ? type : msg;
    } else if (type == "response.incomplete") {
        std::string reason = json_extract_nested(payload, "incomplete_details", "reason");
        ctx->api_error = "response incomplete" + (reason.empty() ? std::string() : ": " + reason);
    }
}

// ---------------------------------------------------------------------------
// JSON delta extractors — one per provider
// ---------------------------------------------------------------------------

/// Extract the content delta from an OpenAI SSE data payload.
/// Payload: {"id":...,"choices":[{"delta":{"content":"<tok>"},...}],...}
static std::string openai_extract_delta(std::string_view payload) {
    auto choices = payload.find("\"choices\"");
    if (choices == std::string_view::npos) return {};
    auto delta = payload.find("\"delta\"", choices);
    if (delta == std::string_view::npos) return {};
    return json_extract_string(payload.substr(delta), "content");
}

/// Extract the text delta from an Anthropic SSE data payload.
/// Relevant events have type "content_block_delta" and delta.type "text_delta".
/// "message_stop" events are handled in write_callback by setting ctx->done.
static std::string anthropic_extract_delta(std::string_view payload,
                                           std::string_view event_type) {
    // Only content_block_delta events carry streaming text
    if (event_type == "content_block_delta" ||
        json_extract_string(payload, "type") == "content_block_delta") {
        return json_extract_nested(payload, "delta", "text");
    }
    return {};
}

/// Route one complete SSE event to the provider's handler.
static void handle_event(StreamCtx* ctx, const SseEvent& ev) {
    const std::string_view payload = ev.data;
    if (payload == "[DONE]") return; // OpenAI end-of-stream marker, nothing to extract

    std::string token;
    if (ctx->provider == Provider::OpenAIResponses) {
        responses_event(ctx, payload);
    } else if (ctx->provider == Provider::OpenAI) {
        token = openai_extract_delta(payload);
    } else {
        // Anthropic signals completion via the message_stop event type
        const bool is_stop =
            ev.event == "message_stop" ||
            json_extract_string(payload, "type") == "message_stop";
        if (!is_stop) {
            token = anthropic_extract_delta(payload, ev.event);
        }
    }

    if (!token.empty() && ctx->on_token) {
        ctx->on_token(token);
        ++ctx->token_count;
    }
}

static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    const size_t total = size * nmemb;
    auto* ctx = static_cast<StreamCtx*>(userdata);

    if (ctx->raw.size() < 2048)
        ctx->raw.append(ptr, (std::min)(total, static_cast<size_t>(2048) - ctx->raw.size()));  // (std::min): windows.h min macro

    ctx->sse.feed(std::string_view(ptr, total), [ctx](const SseEvent& ev) { handle_event(ctx, ev); });
    return total;
}

/// Flush an event left without a closing blank line when the body ends.
static void finish_stream(StreamCtx* ctx) {
    ctx->sse.finish([ctx](const SseEvent& ev) { handle_event(ctx, ev); });
}

// ---------------------------------------------------------------------------
// Hand-rolled JSON body builders
// ---------------------------------------------------------------------------
static std::string json_escape(const std::string& s) {
    std::string out;
    out.reserve(s.size() + 16);
    for (unsigned char c : s) {
        switch (c) {
            case '"':  out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;
            default:
                if (c < 0x20) {
                    char buf[8];
                    snprintf(buf, sizeof(buf), "\\u%04x", static_cast<unsigned>(c));
                    out += buf;
                } else {
                    out += static_cast<char>(c);
                }
        }
    }
    return out;
}

static std::string build_openai_body(const std::string& prompt, const Config& cfg) {
    std::string b;
    b  = "{\"model\":\""      + json_escape(cfg.model) + "\","
         "\"stream\":true,"
         "\"max_tokens\":"    + std::to_string(cfg.max_tokens) + ","
         "\"temperature\":"   + std::to_string(cfg.temperature) + ","
         "\"messages\":[";
    if (!cfg.system_prompt.empty())
        b += "{\"role\":\"system\",\"content\":\"" + json_escape(cfg.system_prompt) + "\"},";
    b += "{\"role\":\"user\",\"content\":\"" + json_escape(prompt) + "\"}]}";
    return b;
}

/// Reasoning models reject `temperature` on the Responses API.
static bool rejects_temperature(const std::string& model) {
    for (const char* p : {"o1", "o3", "o4", "gpt-5"}) {
        if (model.rfind(p, 0) == 0) return true;
    }
    return false;
}

static std::string build_responses_body(const std::string& prompt, const Config& cfg) {
    std::string b = "{\"model\":\"" + json_escape(cfg.model) + "\","
                    "\"stream\":true,"
                    "\"max_output_tokens\":" + std::to_string(cfg.max_tokens) + ",";
    if (!rejects_temperature(cfg.model))
        b += "\"temperature\":" + std::to_string(cfg.temperature) + ",";
    if (!cfg.system_prompt.empty())
        b += "\"instructions\":\"" + json_escape(cfg.system_prompt) + "\",";
    b += "\"input\":\"" + json_escape(prompt) + "\"}";
    return b;
}

static std::string build_anthropic_body(const std::string& prompt, const Config& cfg) {
    std::string b;
    b  = "{\"model\":\""    + json_escape(cfg.model) + "\","
         "\"stream\":true,"
         "\"max_tokens\":"  + std::to_string(cfg.max_tokens) + ",";
    if (!cfg.system_prompt.empty())
        b += "\"system\":\"" + json_escape(cfg.system_prompt) + "\",";
    b += "\"messages\":[{\"role\":\"user\",\"content\":\"" + json_escape(prompt) + "\"}]}";
    return b;
}

// ---------------------------------------------------------------------------
// Core SSE driver — each call is fully self-contained and thread-safe.
// ---------------------------------------------------------------------------
static void do_stream(
    const std::string& url,
    const std::string& json_body,
    const CurlSlist&   headers,
    Provider           provider,
    TokenCallback      on_token,
    DoneCallback       on_done,
    ErrorCallback      on_error)
{
    CurlHandle curl;
    if (!curl.ok()) {
        if (on_error) on_error("Failed to initialize curl handle");
        return;
    }

    StreamCtx ctx;
    ctx.provider = provider;
    ctx.on_token = on_token;

    const auto t0 = std::chrono::steady_clock::now();

    curl_easy_setopt(static_cast<CURL*>(curl), CURLOPT_URL,           url.c_str());
    curl_easy_setopt(static_cast<CURL*>(curl), CURLOPT_HTTPHEADER,    headers.list);
    curl_easy_setopt(static_cast<CURL*>(curl), CURLOPT_POSTFIELDS,    json_body.c_str());
    curl_easy_setopt(static_cast<CURL*>(curl), CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(static_cast<CURL*>(curl), CURLOPT_WRITEDATA,     &ctx);
    curl_easy_setopt(static_cast<CURL*>(curl), CURLOPT_FOLLOWLOCATION,1L);
    curl_easy_setopt(static_cast<CURL*>(curl), CURLOPT_TIMEOUT,       120L);

    const CURLcode res = curl_easy_perform(static_cast<CURL*>(curl));

    const double ms = std::chrono::duration<double, std::milli>(
        std::chrono::steady_clock::now() - t0).count();

    if (res != CURLE_OK) {
        if (on_error) on_error(curl_easy_strerror(res));
        return;
    }
    finish_stream(&ctx);

    long http_code = 0;
    curl_easy_getinfo(static_cast<CURL*>(curl), CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code >= 400) {
        std::string msg = "HTTP error " + std::to_string(http_code);
        std::string detail = json_extract_nested(ctx.raw, "error", "message");
        if (!detail.empty()) msg += ": " + detail;
        if (on_error) on_error(msg);
        return;
    }

    if (provider == Provider::OpenAIResponses) {
        if (!ctx.api_error.empty()) {
            if (on_error) on_error(ctx.api_error);
            return;
        }
        if (!ctx.completed) {
            if (on_error) on_error("stream ended before response.completed");
            return;
        }
    }

    if (on_done) {
        StreamStats stats;
        stats.token_count    = ctx.token_count;
        stats.elapsed_ms     = ms;
        stats.tokens_per_sec = (ms > 0.0) ? (ctx.token_count / (ms / 1000.0)) : 0.0;
        stats.input_tokens   = ctx.input_tokens;
        stats.output_tokens  = ctx.output_tokens;
        stats.response_id    = ctx.response_id;
        on_done(stats);
    }
}

} // namespace detail

// ---------------------------------------------------------------------------
// Public function definitions
// ---------------------------------------------------------------------------

void stream_openai(
    const std::string& prompt, const Config& config,
    TokenCallback on_token, DoneCallback on_done, ErrorCallback on_error)
{
    detail::CurlSlist headers;
    headers.append(("Authorization: Bearer " + config.api_key).c_str());
    headers.append("Content-Type: application/json");
    detail::do_stream(
        "https://api.openai.com/v1/chat/completions",
        detail::build_openai_body(prompt, config),
        headers, detail::Provider::OpenAI,
        on_token, on_done, on_error);
}

void stream_anthropic(
    const std::string& prompt, const Config& config,
    TokenCallback on_token, DoneCallback on_done, ErrorCallback on_error)
{
    detail::CurlSlist headers;
    headers.append(("x-api-key: " + config.api_key).c_str());
    headers.append("anthropic-version: 2023-06-01");
    headers.append("Content-Type: application/json");
    detail::do_stream(
        "https://api.anthropic.com/v1/messages",
        detail::build_anthropic_body(prompt, config),
        headers, detail::Provider::Anthropic,
        on_token, on_done, on_error);
}

void stream_openai_responses(
    const std::string& prompt, const Config& config,
    TokenCallback on_token, DoneCallback on_done, ErrorCallback on_error)
{
    detail::CurlSlist headers;
    headers.append(("Authorization: Bearer " + config.api_key).c_str());
    headers.append("Content-Type: application/json");
    detail::do_stream(
        "https://api.openai.com/v1/responses",
        detail::build_responses_body(prompt, config),
        headers, detail::Provider::OpenAIResponses,
        on_token, on_done, on_error);
}

void stream(
    const std::string& prompt, const Config& config,
    TokenCallback on_token, DoneCallback on_done, ErrorCallback on_error)
{
    if (config.model.rfind("claude-", 0) == 0)
        stream_anthropic(prompt, config, on_token, on_done, on_error);
    else
        stream_openai(prompt, config, on_token, on_done, on_error);
}

} // namespace llm

#endif // LLM_STREAM_IMPLEMENTATION

#endif // LLM_STREAM_NO_CURL
