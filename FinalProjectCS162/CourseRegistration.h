#pragma once

#include "Date.h"

class CourseRegistration {
private:
	Date startDate, endDate;
public:
	Date getStartDate() const;
	Date getEndDate() const;
};