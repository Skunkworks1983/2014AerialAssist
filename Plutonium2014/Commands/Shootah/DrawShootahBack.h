#ifndef __DRAW_SHOOTAH_BACK_H
#define __DRAW_SHOOTAH_BACK_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author David
 */
class DrawShootahBack: public CommandBase {
public:
	DrawShootahBack();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
