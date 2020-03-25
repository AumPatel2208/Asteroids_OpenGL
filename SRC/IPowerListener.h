#pragma once
#ifndef __IPOWERLISTENER_H__
#define __IPOWERLISTENER_H__

class IPowerListener
{
public:
	virtual void OnScoreChanged(int score) = 0;
};

#endif
