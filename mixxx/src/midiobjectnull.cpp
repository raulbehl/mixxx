/***************************************************************************
                          midiobjectnull.cpp  -  description
                             -------------------
    begin                : Thu Jul 4 2002
    copyright            : (C) 2002 by Tue & Ken Haste Andersen
    email                : haste@diku.dk
***************************************************************************/

/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/

#include "midiobjectnull.h"

MidiObjectNull::MidiObjectNull(QString device) : MidiObject(device)
{
}

MidiObjectNull::~MidiObjectNull()
{
}

void MidiObjectNull::devOpen(QString)
{
}

void MidiObjectNull::devClose()
{
}
