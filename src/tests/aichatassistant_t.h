#ifndef Header_AIChatAssistant_T
#define Header_AIChatAssistant_T
#ifndef QT_NO_DEBUG

#include "mostQtHeaders.h"
#include "aichatassistant.h"
#include "testutil.h"
#include <QtTest/QtTest>

class AIChatAssistantTest: public QObject{
	Q_OBJECT
private slots:
	void streamDeltaText_data() {
		QTest::addColumn<QStringList>("reads");
		QTest::addColumn<QString>("text");

		QTest::newRow("openai") << QStringList({
				"data: {\"choices\":[{\"delta\":{\"content\":\"Hel\"}}]}\n\n"
				"data: {\"choices\":[{\"delta\":{\"content\":\"lo\"}}]}\n\ndata: [DONE]\n\n"})
			<< "Hello";
		QTest::newRow("openai event split across reads") << QStringList({
				"data: {\"choices\":[{\"delta\":{\"content\":\"Hel\"}}]}\n\ndata: {\"choi",
				"ces\":[{\"delta\":{\"content\":\"lo\"}}]}\r\n\r",
				"\ndata: [DONE]\n\n"})
			<< "Hello";
		QTest::newRow("anthropic") << QStringList({
				"event: message_start\ndata: {\"type\":\"message_start\",\"message\":{}}\n\n"
				"event: content_block_delta\ndata: {\"type\":\"content_block_delta\",\"index\":0,\"delta\":{\"type\":\"text_delta\",\"text\":\"Hel\"}}\n\n",
				"event: content_block_delta\ndata: {\"type\":\"content_block_delta\",\"index\":0,\"delta\":{\"type\":\"text_delta\",\"text\":\"lo\"}}\n\n"
				"event: message_stop\ndata: {\"type\":\"message_stop\"}\n\n"})
			<< "Hello";
	}

	void streamDeltaText() {
		QFETCH(QStringList, reads);
		QFETCH(QString, text);
		QString result;
		llm::SseParser parser;
		const llm::SseCallback onEvent=[&result](const llm::SseEvent &ev){
			result+=AIChatAssistant::streamDeltaText(ev.data);
		};
		for(const QString &read:reads){
			const QByteArray bytes=read.toUtf8();
			parser.feed(std::string_view(bytes.constData(),static_cast<size_t>(bytes.size())),onEvent);
		}
		parser.finish(onEvent);
		QEQUAL(result,text);
	}
};

#endif // QT_NO_DEBUG
#endif // Header_AIChatAssistant_T
