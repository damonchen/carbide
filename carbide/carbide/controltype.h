#pragma once

#include "automation/include/UIAutomationCore.h"

struct KeyValue{
	const char *name;
	CONTROLTYPEID id;
};

CString FindControlType(CONTROLTYPEID id);