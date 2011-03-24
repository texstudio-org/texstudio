#include "osm.h"

#include <QXmlReader>

Way::Way():flags(Way::WF_NONE){}

class OSMDataHandler: public QXmlDefaultHandler{
public:
	OSMDataHandler(OSMData& osmdata);
	virtual bool startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts );
	virtual bool endElement ( const QString & namespaceURI, const QString & localName, const QString & qName ) ;
private:
	OSMData& osm;
	qint64 openway;
};

OSMDataHandler::OSMDataHandler(OSMData& osmdata):osm(osmdata),openway(-1){

}

bool OSMDataHandler::startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts ){
	if (localName == "node") {
		//node
		Node n;
		n.lat = atts.value("lat").toFloat();
		n.lon = atts.value("lon").toFloat();
		osm.nodes.insert(atts.value("id").toLongLong(), n);
	} else if (localName == "way") {
		openway = atts.value("id").toLongLong();
		Way w;
		w.id = openway;
		osm.ways.append(w);
	} else if (localName == "nd") {
		//node in way
		Q_ASSERT(openway>0);
		Q_ASSERT(openway == osm.ways.last().id);
		osm.ways.last().nodes.append(atts.value("ref").toLongLong());
	}
	return true;
}

bool OSMDataHandler::endElement ( const QString & namespaceURI, const QString & localName, const QString & qName ) {
	if (openway > -1){
		Q_ASSERT(openway == osm.ways.last().id);		
		if (localName == "way") {
			openway = -1;
			if (osm.ways.last().nodes.size() > 0 &&
			    osm.ways.last().nodes.first() == osm.ways.last().nodes.last())
				osm.ways.last().flags |= Way::WF_FILL;
		}
	}
	return true;
}

OSMData::OSMData()
{
}


void OSMData::loadFromFile(const QString& filename){
	nodes.clear();
	ways.clear();
	QXmlSimpleReader xml;
	QXmlInputSource source(&QFile(filename));
	OSMDataHandler handler(*this);
	xml.setContentHandler(&handler);
	xml.setErrorHandler(&handler);
	xml.parse(source);
}
