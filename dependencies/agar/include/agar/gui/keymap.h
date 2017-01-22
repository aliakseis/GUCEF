/*	Public domain	*/

#ifndef _AGAR_WIDGET_KEYMAP_H_
#define _AGAR_WIDGET_KEYMAP_H_
#include <agar/gui/begin.h>

struct ag_editable;
struct ag_editable_buffer;

struct ag_keycode {
	AG_KeySym key;
	const char *modFlags;
	int (*func)(struct ag_editable *, struct ag_editable_buffer *buf,
	            AG_KeySym ks, Uint mod, Uint32 ch);
	const char *flags;
};

struct ag_key_composition {
	Uint32 comp;		/* First key */
	Uint32 key;		/* Second key */
	Uint32 res;		/* Resulting character */
};

struct ag_key_mapping {
	AG_KeySym key;		/* Key */
	Uint modmask;		/* Modifier mask */
	Uint32 unicode;		/* UCS-4 mapping */
};

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC const struct ag_keycode agKeymap[];
extern DECLSPEC const struct ag_key_mapping agKeymapLATIN1[];
extern DECLSPEC const struct ag_key_composition agCompositionMap[];
extern DECLSPEC const int agCompositionMapSize;
extern DECLSPEC Uint32 AG_ApplyModifiersASCII(Uint32, int);
extern DECLSPEC int AG_KeyInputCompose(struct ag_editable *, Uint32, Uint32 *);
__END_DECLS
/* Close generated block */

#include <agar/gui/close.h>
#endif	/* _AGAR_WIDGET_KEYMAP_H_ */
