/*-
 * Copyright (c) 2009-2013 Hans Petter Selasky. All rights reserved.
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

#ifndef _MIDIPP_H_
#define	_MIDIPP_H_

#include <stdint.h>
#include <sys/param.h>

#include <err.h>

#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>
#include <QScrollBar>
#include <QPlainTextEdit>
#include <QTabWidget>
#include <QLabel>
#include <QSpinBox>
#include <QTextCursor>
#include <QTimer>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QFile>
#include <QFileDialog>
#include <QLineEdit>
#include <QSpacerItem>
#include <QLCDNumber>
#include <QPicture>
#include <QColor>
#include <QPaintEvent>
#include <QPainter>
#include <QFont>
#include <QPrintDialog>
#include <QPrinter>
#include <QFontDialog>
#include <QFontInfo>
#include <QFileInfo>
#include <QMouseEvent>
#include <QSizePolicy>
#include <QListWidget>
#include <QIcon>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDir>
#include <QGroupBox>
#include <QSettings>
#include <QStyle>
#include <QSlider>
#include <QtNetwork>
#include <QUrl>
#include <QWheelEvent>
#include <QColorDialog>

#include <umidi20.h>

#define	MPP_MAX_BUTTON_MAP	16
#define	MPP_MAX_VIEWS	2
#define	MPP_MAX_LINES	8192
#define	MPP_MAX_SCORES	32
#define	MPP_MAX_LABELS	32
#define	MPP_MAX_QUEUE	32
#define	MPP_MAX_DEVS	8
#define	MPP_MAX_BPM	32
#define	MPP_MAX_LBUTTON	16
#define	MPP_MIN_POS	4	/* ticks */
#define	MPP_PRESSED_MAX	128
#define	MPP_MAX_DURATION 255	/* inclusive */
#define	MPP_MAGIC_DEVNO	(UMIDI20_N_DEVICES - 1)
#define	MPP_ICON_FILE	":/midipp.png"
#define	MPP_DEFAULT_URL "http://home.selasky.org:8192/midipp/database.tar.gz"
#define	MPP_DEFAULT_CMD_KEY C3
#define	MPP_DEFAULT_BASE_KEY C5
#define	MPP_VISUAL_MARGIN	8
#define	MPP_VISUAL_R_MAX	8
#define	MPP_VISUAL_C_MAX	20
#define	MPP_VOLUME_UNIT		127
#define	MPP_VOLUME_MAX		511	/* inclusivly */
#define	MPP_CUSTOM_MAX		10
#define	MPP_LOOP_MAX		8

#define	STRLCPY(a,b,c) do { \
    strncpy(a,b,c); ((char *)(a))[(c)-1] = 0; \
} while (0)

class MppCheckBox;
class MppBpm;
class MppButton;
class MppButtonMap;
class MppCustomTab;
class MppDataBase;
class MppDecode;
class MppDevices;
class MppElement;
class MppGPro;
class MppGroupBox;
class MppGridLayout;
class MppHead;
class MppImportTab;
class MppLoopTab;
class MppMainWindow;
class MppMidi;
class MppMode;
class MppPattern;
class MppReplace;
class MppScoreHighLighter;
class MppScoreMain;
class MppScoreView;
class MppSettings;
class MppSettingsWhat;
class MppShowControl;
class MppShowWidget;
class MppSpinBox;
class MppVolume;

struct MppChordElement;

class QPrinter;

struct MppScoreEntry {
	uint8_t key;
	uint8_t dur;
	uint8_t channel;
};

struct MppInstr {
	uint16_t bank;
	uint8_t prog;
	uint8_t muted;
	uint8_t updated;
};

struct MppVisualDot {
	qreal x_off;
	qreal y_off;
};

struct MppVisualScore {
	QPicture *pic;
	struct MppVisualDot *pdot;
	MppElement *start;
	MppElement *stop;
	int newpage;
	int ndot;
};

extern QColor color_black;
extern QColor color_white;
extern QColor color_grey;
extern QColor color_logo;
extern QColor color_green;

extern QString MppVariantList;
extern QString MppHomeDirTxt;
extern QString MppHomeDirMid;
extern QString MppHomeDirGp3;
extern QString MppHomeDirBackground;

extern QString MppBaseName(QString fname);
extern char *MppQStringToAscii(QString s);
extern QString MppReadFile(QString fname);
extern void MppWriteFile(QString fname, QString text);
extern uint8_t MppReadRawFile(QString fname, QByteArray *pdata);
extern uint8_t MppWriteRawFile(QString fname, QByteArray *pdata);
extern const char *MppBaseKeyToString(int key, int sharp);
extern void MppScoreVariantInit(void);

#endif	/* _MIDIPP_H_ */
