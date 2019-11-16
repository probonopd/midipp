/*-
 * Copyright (c) 2011-2019 Hans Petter Selasky. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "midipp.h"

#include "midipp_chansel.h"
#include "midipp_devsel.h"
#include "midipp_buttonmap.h"
#include "midipp_mode.h"
#include "midipp_spinbox.h"
#include "midipp_scores.h"
#include "midipp_mainwindow.h"
#include "midipp_checkbox.h"
#include "midipp_groupbox.h"
#include "midipp_volume.h"

MppMode :: MppMode(MppScoreMain *_parent, uint8_t _vi)
{
	sm = _parent;
	view_index = _vi;

	gl = new QGridLayout(this);

	gb_iconfig = new MppGroupBox(tr("MIDI input config"));
	gb_oconfig = new MppGroupBox(tr("MIDI output config"));
	gb_contrast = new MppGroupBox(QString());
	gb_delay = new MppGroupBox(QString());

	setWindowTitle(tr("View %1 mode").arg(QChar('A' + _vi)));
	setWindowIcon(QIcon(MppIconFile));

	cbx_norm = new MppCheckBox();
	cbx_norm->setChecked(1);
	connect(cbx_norm, SIGNAL(stateChanged(int,int)), this, SLOT(handle_changed()));

	sli_contrast = new QSlider();
	sli_contrast->setRange(0, 255);
	sli_contrast->setOrientation(Qt::Horizontal);
	sli_contrast->setValue(128);
	connect(sli_contrast, SIGNAL(valueChanged(int)), this, SLOT(handle_contrast_label(int)));
	connect(sli_contrast, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));
	handle_contrast_label(sli_contrast->value());

	but_song_events = new MppButtonMap("Send MIDI song events\0OFF\0ON\0", 2, 2);
	connect(but_song_events, SIGNAL(selectionChanged(int)), this, SLOT(handle_changed()));

	but_mode = new MppKeyModeButtonMap("Input key mode");
	connect(but_mode, SIGNAL(selectionChanged(int)), this, SLOT(handle_changed()));

	but_reset = new QPushButton(tr("Reset"));
	connect(but_reset, SIGNAL(released()), this, SLOT(handle_reset()));

	but_done = new QPushButton(tr("Close"));
	connect(but_done, SIGNAL(released()), this, SLOT(accept()));

	spn_base = new MppSpinBox(0,0);
	spn_base->setValue(0);
	connect(spn_base, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	sli_delay = new QSlider();
	sli_delay->setRange(0, 256);
	sli_delay->setValue(0);
	sli_delay->setOrientation(Qt::Horizontal);
	connect(sli_delay, SIGNAL(valueChanged(int)), this, SLOT(handle_delay_label(int)));
	connect(sli_delay, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));
	handle_delay_label(sli_delay->value());

	spn_input_chan = new MppChanSel(sm->mainWindow, -1, MPP_CHAN_ANY);
	connect(spn_input_chan, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_pri_chan = new MppChanSel(sm->mainWindow, 0, 0);
	connect(spn_pri_chan, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_pri_dev = new MppDevSel(-1, MPP_DEV_ALL);
	connect(spn_pri_dev, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_sec_base_chan = new MppChanSel(sm->mainWindow, -1, MPP_CHAN_NONE);
	connect(spn_sec_base_chan, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_sec_base_dev = new MppDevSel(-1, MPP_DEV_ALL);
	connect(spn_sec_base_dev, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_sec_treb_chan = new MppChanSel(sm->mainWindow, -1, MPP_CHAN_NONE);
	connect(spn_sec_treb_chan, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_sec_treb_dev = new MppDevSel(-1, MPP_DEV_ALL);
	connect(spn_sec_treb_dev, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_pri_volume = new MppVolume();
	spn_pri_volume->setRange(0, MPP_VOLUME_MAX, MPP_VOLUME_UNIT);
	connect(spn_pri_volume, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_sec_base_volume = new MppVolume();
	spn_sec_base_volume->setRange(0, MPP_VOLUME_MAX, MPP_VOLUME_UNIT);
	connect(spn_sec_base_volume, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_sec_treb_volume = new MppVolume();
	spn_sec_treb_volume->setRange(0, MPP_VOLUME_MAX, MPP_VOLUME_UNIT);
	connect(spn_sec_treb_volume, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_aux_chan = new MppChanSel(sm->mainWindow, 0, 0);
	connect(spn_aux_chan, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_aux_base_chan = new MppChanSel(sm->mainWindow, -1, MPP_CHAN_NONE);
	connect(spn_aux_base_chan, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));

	spn_aux_treb_chan = new MppChanSel(sm->mainWindow, -1, MPP_CHAN_NONE);
	connect(spn_aux_treb_chan, SIGNAL(valueChanged(int)), this, SLOT(handle_changed()));
	
	but_note_mode = new MppButtonMap("Output note mode\0" "Normal\0" "SysEx\0", 2, 2);
	connect(but_note_mode, SIGNAL(selectionChanged(int)), this, SLOT(handle_changed()));

	gl->addWidget(gb_iconfig, 0, 0, 2, 2);
	gl->addWidget(gb_oconfig, 2, 2, 3, 2);

	gl->addWidget(gb_delay, 0, 2, 1, 2);
	gl->addWidget(gb_contrast, 1, 2, 1, 2);

	gl->addWidget(but_song_events, 2, 0, 1, 2);
	gl->addWidget(but_note_mode, 3, 0, 1, 2);
	gl->addWidget(but_mode, 4, 0, 1, 2);

	gl->addWidget(but_reset, 5, 0, 1, 2);
	gl->addWidget(but_done, 5, 2, 1, 2);
	gl->setRowStretch(6, 1);
	gl->setColumnStretch(4, 1);

	gb_delay->addWidget(sli_delay, 0, 0, 1, 1);

	gb_contrast->addWidget(sli_contrast, 0, 0, 1, 2);
	gb_contrast->addWidget(new QLabel(tr("Normalize chord pressure")), 1, 0, 1, 1);
	gb_contrast->addWidget(cbx_norm, 1, 1, 1, 1);

	gb_iconfig->addWidget(new QLabel(tr("Play Key")), 0, 0, 1, 1);
	gb_iconfig->addWidget(spn_base, 0, 1, 1, 1);
	gb_iconfig->addWidget(new QLabel(tr("Channel")), 1, 0, 1, 1);
	gb_iconfig->addWidget(spn_input_chan, 1, 1, 1, 1);

	gb_oconfig->addWidget(new QLabel(tr("Main\nchannel")), 0, 1, 1, 1, Qt::AlignCenter);
	gb_oconfig->addWidget(new QLabel(tr("Auxilary\nchannel")), 0, 2, 1, 1, Qt::AlignCenter);
	gb_oconfig->addWidget(new QLabel(tr("Device")), 0, 3, 1, 1, Qt::AlignCenter);
	gb_oconfig->addWidget(new QLabel(tr("Volume")), 0, 4, 1, 1, Qt::AlignCenter);

	gb_oconfig->addWidget(new QLabel(tr("Primary")), 1, 0, 1, 1);
	gb_oconfig->addWidget(spn_pri_chan, 1, 1, 1, 1);
	gb_oconfig->addWidget(spn_aux_chan, 1, 2, 1, 1);
	gb_oconfig->addWidget(spn_pri_dev, 1, 3, 1, 1);
	gb_oconfig->addWidget(spn_pri_volume, 1, 4, 1, 1);

	gb_oconfig->addWidget(new QLabel(tr("Secondary\nbass")), 2, 0, 1, 1);
	gb_oconfig->addWidget(spn_sec_base_chan, 2, 1, 1, 1);
	gb_oconfig->addWidget(spn_aux_base_chan, 2, 2, 1, 1);
	gb_oconfig->addWidget(spn_sec_base_dev, 2, 3, 1, 1);
	gb_oconfig->addWidget(spn_sec_base_volume, 2, 4, 1, 1);

	gb_oconfig->addWidget(new QLabel(tr("Secondary\ntreble")), 3, 0, 1, 1);
	gb_oconfig->addWidget(spn_sec_treb_chan, 3, 1, 1, 1);
	gb_oconfig->addWidget(spn_aux_treb_chan, 3, 2, 1, 1);
	gb_oconfig->addWidget(spn_sec_treb_dev, 3, 3, 1, 1);
	gb_oconfig->addWidget(spn_sec_treb_volume, 3, 4, 1, 1);
}

MppMode :: ~MppMode()
{

}

void
MppMode :: update_all(void)
{
	int base_key;
	int key_delay;
	int channelInput;
	int channel;
	int channelBase;
	int channelTreb;
	int auxChannel;
	int auxChannelBase;
	int auxChannelTreb;
	int device;
	int deviceBase;
	int deviceTreb;
	int volume;
	int volumeBase;
	int volumeTreb;
	int key_mode;
	int note_mode;
	int chord_contrast;
	int chord_norm;
	int song_events;

	sm->mainWindow->atomic_lock();
	base_key = sm->baseKey;
	key_delay = sm->delayNoise;
	channelInput = sm->inputChannel;
	channel = sm->synthChannel;
	channelBase = sm->synthChannelBase;
	channelTreb = sm->synthChannelTreb;
	auxChannel = sm->auxChannel;
	auxChannelBase = sm->auxChannelBase;
	auxChannelTreb = sm->auxChannelTreb;
	device = sm->synthDevice;
	deviceBase = sm->synthDeviceBase;
	deviceTreb = sm->synthDeviceTreb;
	volume = sm->mainWindow->trackVolume[MPP_DEFAULT_TRACK(sm->unit)];
	volumeBase = sm->mainWindow->trackVolume[MPP_BASS_TRACK(sm->unit)];
	volumeTreb = sm->mainWindow->trackVolume[MPP_TREBLE_TRACK(sm->unit)];
	key_mode = sm->keyMode;
	chord_contrast = sm->chordContrast;
	chord_norm = sm->chordNormalize;
	song_events = sm->songEventsOn;
	note_mode = sm->noteMode;
	sm->mainWindow->atomic_unlock();

	spn_base->setValue(base_key);
	sli_delay->setValue(key_delay);
	sli_contrast->setValue(chord_contrast);
	spn_input_chan->setValue(channelInput);
	spn_pri_chan->setValue(channel);
	spn_sec_base_chan->setValue(channelBase);
	spn_sec_treb_chan->setValue(channelTreb);
	spn_aux_chan->setValue(auxChannel);
	spn_aux_base_chan->setValue(auxChannelBase);
	spn_aux_treb_chan->setValue(auxChannelTreb);
	spn_pri_dev->setValue(device);
	spn_sec_base_dev->setValue(deviceBase);
	spn_sec_treb_dev->setValue(deviceTreb);
	spn_pri_volume->setValue(volume);
	spn_sec_base_volume->setValue(volumeBase);
	spn_sec_treb_volume->setValue(volumeTreb);
	but_mode->setSelection(key_mode);
	cbx_norm->setChecked(chord_norm);
	but_song_events->setSelection(song_events);
	but_note_mode->setSelection(note_mode);
}

void
MppMode :: handle_contrast_label(int v)
{
	char buf[32];
	v = ((v - 128) * 100) / 127;

	if (v > 100)
		v = 100;
	else if (v < -100)
		v = -100;

	snprintf(buf, sizeof(buf),
	    "Chord(-) vs Melody(+) (%d%%)", v);
	gb_contrast->setTitle(tr(buf));
}

void
MppMode :: handle_delay_label(int v)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "Random T/F/M key delay (%dms)", v);
	gb_delay->setTitle(tr(buf));
}

void
MppMode :: handle_reset()
{
	sli_contrast->setValue(128);
	sli_delay->setValue(25);
	spn_input_chan->setValue(-1);
	spn_base->setValue(MPP_DEFAULT_BASE_KEY);
	spn_pri_chan->setValue(0);
	spn_sec_base_chan->setValue(-1);
	spn_sec_treb_chan->setValue(-1);
	spn_pri_dev->setValue(-1);
	spn_sec_base_dev->setValue(-1);
	spn_sec_treb_dev->setValue(-1);
	spn_pri_volume->setValue(MPP_VOLUME_UNIT);
	spn_sec_base_volume->setValue(MPP_VOLUME_UNIT);
	spn_sec_treb_volume->setValue(MPP_VOLUME_UNIT);
	cbx_norm->setChecked(1);
	but_mode->setSelection(0);
	but_song_events->setSelection(0);
}

void
MppMode :: handle_changed()
{
	int base_key;
	int key_delay;
	int channelInput;
	int channel;
	int channelBase;
	int channelTreb;
	int auxChannel;
	int auxChannelBase;
	int auxChannelTreb;
	int device;
	int deviceBase;
	int deviceTreb;
	int volume;
	int volumeBase;
	int volumeTreb;
	int key_mode;
	int note_mode;
	int chord_contrast;
	int chord_norm;
	int song_events;

	base_key = spn_base->value();
	key_delay = sli_delay->value();
	channelInput = spn_input_chan->value();
	channel = spn_pri_chan->value();
	channelBase = spn_sec_base_chan->value();
	channelTreb = spn_sec_treb_chan->value();
	auxChannel = spn_aux_chan->value();
	auxChannelBase = spn_aux_base_chan->value();
	auxChannelTreb = spn_aux_treb_chan->value();
	device = spn_pri_dev->value();
	deviceBase = spn_sec_base_dev->value();
	deviceTreb = spn_sec_treb_dev->value();
	volume = spn_pri_volume->value();
	volumeBase = spn_sec_base_volume->value();
	volumeTreb = spn_sec_treb_volume->value();
	chord_contrast = sli_contrast->value();
	chord_norm = cbx_norm->isChecked();
	key_mode = but_mode->currSelection;
	song_events = but_song_events->currSelection;
	note_mode = but_note_mode->currSelection;

	if (key_mode < 0 || key_mode >= MM_PASS_MAX)
		key_mode = 0;

	sm->mainWindow->atomic_lock();
	sm->baseKey = base_key;
	sm->delayNoise = key_delay;
	sm->inputChannel = channelInput;
	sm->synthChannel = channel;
	sm->synthChannelBase = channelBase;
	sm->synthChannelTreb = channelTreb;
	sm->auxChannel = auxChannel;
	sm->auxChannelBase = auxChannelBase;
	sm->auxChannelTreb = auxChannelTreb;
	sm->synthDevice = device;
	sm->synthDeviceBase = deviceBase;
	sm->synthDeviceTreb = deviceTreb;
	sm->mainWindow->trackVolume[MPP_DEFAULT_TRACK(sm->unit)] = volume;
	sm->mainWindow->trackVolume[MPP_BASS_TRACK(sm->unit)] = volumeBase;
	sm->mainWindow->trackVolume[MPP_TREBLE_TRACK(sm->unit)] = volumeTreb;
	sm->keyMode = key_mode;
	sm->chordContrast = chord_contrast;
	sm->chordNormalize = chord_norm;
	sm->songEventsOn = song_events;
	sm->noteMode = note_mode;
	sm->mainWindow->atomic_unlock();
}
