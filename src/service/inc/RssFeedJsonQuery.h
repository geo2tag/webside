#ifndef _RSSFEEDJSONQUERY_H_INCLUDED
#define _RSSFEEDJSONQUERY_H_INCLUDED

#include "DataMarks.h"
#include "Channel.h"
#include "Handle.h"
#include "elements.h"
#include "quick.h"
#include "reader.h"
#include "writer.h"
#include "cast.h"
#include "exception.h"
#include <sstream>
#include "IJsonQuery.h"


class RssFeedJsonQuery:public IJsonQuery
{
	std::string m_token;
	double m_latitude;
	double m_longitude;
	double m_radius;
	std::string outToString() const;
	CHandlePtr<common::DataMarks> m_marks;
	void init(const std::stringstream& query);
public:
	
	RssFeedJsonQuery();
	void process();
};

#endif
