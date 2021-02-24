/** Function to shift the current view to the left/right
 *
 * @param: "arg->i" stores the number of tags to shift right (positive value)
 *          or left (negative value)
 */

#define SHIFT_LEFT              1 << 0
#define SHIFT_RIGHT             1 << 1
#define SHIFT_TAG		1 << 2
#define SHIFT_VIEW		1 << 3


{ MODKEY,           XK_o,  shiftview,      { .ui = SHIFT_RIGHT | SHIFT_VIEW } },
{ MODKEY,           XK_i,   shiftview,      { .ui = SHIFT_LEFT | SHIFT_VIEW} },
{ MODKEY|ShiftMask, XK_o,  shiftview,      { .ui = SHIFT_RIGHT | SHIFT_TAG | SHIFT_VIEW} },
{ MODKEY|ShiftMask, XK_i,   shiftview,      { .ui = SHIFT_LEFT | SHIFT_TAG | SHIFT_VIEW} },

void
shiftview(const Arg *arg) {
	Arg shifted;
	unsigned int a = arg->ui;

	if(a & SHIFT_LEFT) // left circular shift
		shifted.ui = (selmon->tagset[selmon->seltags] << 1)
		   | (selmon->tagset[selmon->seltags] >> (LENGTH(tags) - 1));

	else if(a & SHIFT_RIGHT) // right circular shift
		shifted.ui = selmon->tagset[selmon->seltags] >> 1
		   | selmon->tagset[selmon->seltags] << (LENGTH(tags) - 1);

	if(a & SHIFT_TAG) 
		tag(&shifted);
	
	if(a & SHIFT_VIEW)
		view(&shifted);
}
