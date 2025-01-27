/*-
 * Copyright (c) 2011-2022 Hans Petter Selasky. All rights reserved.
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

#ifndef _MIDIPP_DEVICES_H_
#define	_MIDIPP_DEVICES_H_

#include "midipp.h"

class MppDevices : public QDialog
{
	Q_OBJECT;
public:
	MppDevices(QWidget *parent = 0);
	~MppDevices();

	int autoSelect();

	QGridLayout *gl;

	MppGroupBox *gb_rec;
	MppGroupBox *gb_play;

	QListWidget *lw_rec;
	QListWidget *lw_play;

	QPushButton *but_ok;
	QPushButton *but_cancel;

	const char **rec_alsa_str;
	const char **play_alsa_str;

	const char **rec_jack_str;
	const char **play_jack_str;

	const char **rec_coremidi_str;
	const char **play_coremidi_str;

	const char **rec_android_str;
	const char **play_android_str;

	QString rec_dev;
	QString play_dev;
	QString result_dev;

public slots:
	void accept(void);
};

#endif			/* _MIDIPP_DEVICES_H_ */
