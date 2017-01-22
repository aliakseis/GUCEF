/*
 * Copyright (c) 2005-2010 Hypertriton, Inc. <http://hypertriton.com/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <agar/config/enable_gui.h>
#ifdef ENABLE_GUI

#include <agar/core/core.h>

#include <agar/gui/widget.h>
#include <agar/gui/window.h>
#include <agar/gui/button.h>
#include <agar/gui/primitive.h>
#include <agar/gui/text_cache.h>

#include <agar/math/m.h>
#include <agar/math/m_matview.h>
#include <agar/math/m_gui.h>

M_Matview *
M_MatviewNew(void *parent, M_Matrix *M, Uint flags)
{
	M_Matview *mv;

	mv = Malloc(sizeof(M_Matview));
	AG_ObjectInit(mv, &mMatviewClass);
	mv->flags |= flags;
	if (M != NULL) {
		M_MatviewSetMatrix(mv, M);
	}
	AG_ObjectAttach(parent, mv);
	return (mv);
}

void
M_MatviewSetMatrix(M_Matview *mv, M_Matrix *M)
{
	M_MatrixFPU *MFPU = (void *)M;

	if (strcmp(M->ops->name, "scalar") != 0) {
		AG_FatalError("Cannot display %s matrices",
		    M->ops->name);
	}
	AG_ObjectLock(mv);
	mv->matrix = MMATRIX(MFPU);
	mv->mPre = MROWS(MFPU);
	mv->nPre = MCOLS(MFPU);
	AG_BindInt(mv->hBar, "max", (int *)&MMATRIX(mv->matrix)->m);
	AG_BindInt(mv->vBar, "max", (int *)&MMATRIX(mv->matrix)->n);
	AG_ObjectUnlock(mv);
	AG_Redraw(mv);
}

static void
KeyDown(AG_Event *event)
{
	M_Matview *mv = AG_SELF();
	int keysym = AG_INT(1);

	switch (keysym) {
	case AG_KEY_G:
		M_MatviewSetDisplayMode(mv, M_MATVIEW_GREYSCALE);
		break;
	case AG_KEY_N:
		M_MatviewSetDisplayMode(mv, M_MATVIEW_NUMERICAL);
		break;
	case AG_KEY_EQUALS:
		mv->scale++;
		AG_Redraw(mv);
		break;
	case AG_KEY_MINUS:
		if (mv->scale-1 >= 0) {
			mv->scale--;
		}
		AG_Redraw(mv);
		break;
	}
}

static void
MouseButtonDown(AG_Event *event)
{
	AG_Button *bu = AG_SELF();

	AG_WidgetFocus(bu);
}

static void
Init(void *obj)
{
	M_Matview *mv = obj;

	WIDGET(mv)->flags |= AG_WIDGET_EXPAND|AG_WIDGET_FOCUSABLE;

	mv->mode = M_MATVIEW_NUMERICAL;
	mv->matrix = NULL;
	mv->flags = 0;
	mv->hSpacing = 2;
	mv->vSpacing = 2;
	mv->hBar = AG_ScrollbarNew(mv, AG_SCROLLBAR_HORIZ, AG_SCROLLBAR_EXCL);
	mv->vBar = AG_ScrollbarNew(mv, AG_SCROLLBAR_VERT, AG_SCROLLBAR_EXCL);
	mv->xOffs = 0;
	mv->yOffs = 0;
	mv->scale = 8;
	mv->mPre = 0;
	mv->nPre = 0;
	mv->numFmt = "%g";
	mv->tCache = AG_TextCacheNew(mv, 64, 2);
	mv->r = AG_RECT(0,0,0,0);
	
	AG_BindInt(mv->hBar, "value", &mv->xOffs);
	AG_BindInt(mv->vBar, "value", &mv->yOffs);
	AG_SetInt(mv->hBar, "min", 0);
	AG_SetInt(mv->vBar, "min", 0);

	AG_TextSize("-00", &mv->wEnt, &mv->hEnt);

	AG_SetEvent(mv, "key-down", KeyDown, NULL);
	AG_SetEvent(mv, "mouse-button-down", MouseButtonDown, NULL);
}

static void
Destroy(void *obj)
{
	M_Matview *mv = obj;

	AG_TextCacheDestroy(mv->tCache);
}

void
M_MatviewSetDisplayMode(M_Matview *mv, enum m_matview_mode mode)
{
	AG_ObjectLock(mv);
	mv->mode = mode;
	AG_ObjectUnlock(mv);
	AG_Redraw(mv);
}

void
M_MatviewSetNumericalFmt(M_Matview *mv, const char *fmt)
{
	AG_ObjectLock(mv);
	mv->numFmt = fmt;
	AG_ObjectUnlock(mv);
	AG_Redraw(mv);
}

void
M_MatviewSizeHint(M_Matview *mv, const char *text, Uint m, Uint n)
{
	AG_ObjectLock(mv);
	mv->mPre = m;
	mv->nPre = n;
	AG_TextSize(text, &mv->wEnt, &mv->hEnt);
	AG_ObjectUnlock(mv);
}

static void
SizeRequest(void *obj, AG_SizeReq *r)
{
	M_Matview *mv = obj;

	r->w = mv->nPre*(mv->wEnt + mv->hSpacing) + mv->hSpacing*2;
	r->h = mv->mPre*(mv->hEnt + mv->vSpacing) + mv->vSpacing*2;
}

static int
SizeAllocate(void *obj, const AG_SizeAlloc *a)
{
	M_Matview *mv = obj;
	AG_SizeAlloc aBar;

	mv->r.w = a->w;
	mv->r.h = a->h;

	aBar.x = 0;
	aBar.y = a->h - mv->hBar->width;
	aBar.w = a->w;
	aBar.h = mv->hBar->width+1;
	AG_WidgetSizeAlloc(mv->hBar, &aBar);
	mv->r.h -= HEIGHT(mv->hBar);

	aBar.x = a->w - mv->vBar->width;
	aBar.y = mv->vBar->width;
	aBar.w = mv->vBar->width;
	aBar.h = a->h - mv->hBar->width+1;
	AG_WidgetSizeAlloc(mv->vBar, &aBar);
	mv->r.w -= WIDTH(mv->vBar);

	return (0);
}

static void
DrawNumerical(void *p)
{
	char text[8];
	M_Matview *mv = p;
	M_Matrix *M = mv->matrix;
	int m, n;
	int x, y;
	int xMin = 5, xMax = 0;
	int xOffs = -mv->xOffs*mv->wEnt + 8;
	int yOffs = -mv->yOffs*mv->hEnt + 8;

	AG_DrawBox(mv, mv->r, -1, WCOLOR(mv,0));
	AG_PushClipRect(mv, mv->r);
	
	AG_PushTextState();
	AG_TextColor(WCOLOR(mv,TEXT_COLOR));

	for (m = 0, y = yOffs;
	     m < MROWS(M) && y < mv->r.h;
	     m++, y += (mv->hEnt + mv->vSpacing)) {
		for (n = 0, x = xOffs;
		     n < MCOLS(M) && x < mv->r.w;
		     n++, x += (mv->wEnt + mv->hSpacing)) {
			int su;

			Snprintf(text, sizeof(text), mv->numFmt, M_Get(M,m,n));
			if ((su = AG_TextCacheGet(mv->tCache,text)) != -1) {
				AG_WidgetBlitSurface(mv, su, x, y);
				xMax = MAX(xMax, x+WSURFACE(mv,su)->w);
			}
			xMin = MIN(xMin, x);
		}
	}
	
	AG_DrawLineV(mv, xMin-2, 2, y, WCOLOR(mv,LINE_COLOR));
	AG_DrawLineV(mv, xMax+4, 2, y, WCOLOR(mv,LINE_COLOR));

	AG_PopTextState();
	AG_PopClipRect(mv);
}

static void
DrawGreyscale(void *p)
{
	M_Matview *mv = p;
	M_Matrix *A = mv->matrix;
	Uint m, n;
	int x, y;
	M_Real big = 0.0, small = 0.0;
	int xOffs = -mv->xOffs*mv->scale;
	int yOffs = -mv->yOffs*mv->scale;

	AG_DrawBox(mv, mv->r, -1, WCOLOR(mv,0));
	AG_PushClipRect(mv, mv->r);

	for (m = 0; m < MROWS(A); m++) {
		for (n = 0; n < MCOLS(A); n++) {
			if (M_Get(A,m,n) == 0.0) { continue; }
			if (M_Get(A,m,n) > big) { big = M_Get(A,m,n); }
			if (M_Get(A,m,n) < small) { small = M_Get(A,m,n); }
		}
	}
	big -= small;

	for (m = 0, y = yOffs;
	     m < MROWS(A) && y < mv->r.h;
	     m++, y += mv->scale) {
		for (n = 0, x = xOffs;
		     n < MCOLS(A) && x < mv->r.w;
		     n++, x += mv->scale) {
		     	M_Real dv = M_Get(A,m,n);
			AG_Color c;
			Uint8 v;

			if (dv == 0.0) {
				continue;
			}
			if (dv == HUGE_VAL) {
				c = AG_ColorRGB(200,0,0);
			} else {
				if (dv >= 0.0) {
					v = 127 + (Uint8)(dv*127.0/big);
					c = AG_ColorRGB(v,0,0);
				} else {
					v = 127 + (Uint8)(Fabs(dv)*127.0/big);
					c = AG_ColorRGB(0,0,v);
				}
			}
			AG_DrawRectFilled(mv,
			    AG_RECT(x,y,mv->scale,mv->scale),
			    c);
		}
	}
	AG_PopClipRect(mv);
}

static void
Draw(void *obj)
{
	M_Matview *mv = obj;

	if (mv->mode == M_MATVIEW_NUMERICAL) {
		DrawNumerical(mv);
	} else {
		DrawGreyscale(mv);
	}
}

AG_WidgetClass mMatviewClass = {
	{
		"AG_Widget:M_Matview",
		sizeof(M_Matview),
		{ 0,0 },
		Init,
		NULL,			/* free */
		Destroy,
		NULL,			/* load */
		NULL,			/* save */
		NULL			/* edit */
	},
	Draw,
	SizeRequest,
	SizeAllocate
};

#endif /* ENABLE_GUI */
