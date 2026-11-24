#ifndef LLM_STREAM_HPP
#define LLM_STREAM_HPP

// Server-Sent Events parser from llm-stream v0.3.0, https://github.com/Mattbusel/llm-stream
// MIT License, Copyright (c) Matthew Busel. Only the SSE parser is included here.

#include <functional>
#include <string>
#include <string_view>

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
    /// Forget all state, including the last event id.
    void reset() { *this = SseParser(); }

private:
    inline void process_line(const SseCallback& on_event);
    inline void dispatch(const SseCallback& on_event);

    std::string line_;            ///< Partial line carried over between chunks
    std::string event_;           ///< Event type buffer
    std::string data_;            ///< Data buffer, each line followed by '\n'
    std::string id_;              ///< Last event id buffer
    bool        skip_lf_  = false; ///< The previous chunk ended in CR: drop a leading LF
    bool        first_line_ = true; ///< Strip a UTF-8 BOM from the first line
};

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

#endif // LLM_STREAM_HPP
