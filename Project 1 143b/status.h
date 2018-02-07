#pragma once
#ifndef STATUS_H
#define STATUS_H

//Process status enum
enum pStatus {
	READY,
	BLOCKED,
	RUNNING
};

//Resource status enum
enum rStatus {
	FREE,
	ALLOCATED
};
#endif //STATUS_H