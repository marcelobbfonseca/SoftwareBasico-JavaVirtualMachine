#include<stdint.h>

namespace Stack
{
	union stack_map_frame
	{
		uint8_t same_frame;
		same_locals_1_stack_item_frame;
		same_locals_1_stack_item_frame_extended;
		chop_frame;
		same_frame_extended;
		append_frame;
		full_frame;
	}
}
