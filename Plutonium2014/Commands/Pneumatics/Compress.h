#ifndef __COMPRESS_H
#define __COMPRESS_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Compress: public CommandBase {
public:
	Compress();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
