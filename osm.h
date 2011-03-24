#ifndef OSM_H
#define OSM_H

#include <QMap>
#include <QPointF>

typedef qint64 OSMNodeId;

struct Node{
	float lat, lon;
	//int flags;
};
struct Way{
	Way();
	enum Flags {WF_NONE = 0, WF_FILL = 1};
	qint64 id;
	QList<OSMNodeId> nodes;
	int flags;
};

class OSMData
{
public:
	OSMData();
	void loadFromFile(const QString& filename);
	QMap<OSMNodeId, Node> nodes;
	QList<Way> ways;
};

#endif // OSM_H
