#ifndef __SHIFT_H
#define __SHIFT_H

#include "../../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Shift: public CommandBase {
	enum ShiftStyle {
		kLow,
		kHigh,
		kToggle
	};
	ShiftStyle style;
	
public:
	Shift(ShiftStyle style = kToggle);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
