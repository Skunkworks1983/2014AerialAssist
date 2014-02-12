#ifndef __UPDATE_COMPRESSOR_H
#define __UPDATE_COMPRESSOR_H

#include "../CommandBase.h"

/**
 * C
 *
 * @author Ross Bajocich
 */
class UpdateCompressor: public CommandBase {
public:
	UpdateCompressor();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
