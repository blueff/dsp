#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "codec.h"

#include "codecs/sndfile.h"
#include "codecs/alsa.h"
#include "codecs/mp3.h"
#include "codecs/null.h"

struct codec_info {
	const char *type;
	const char **ext;  /* null terminated array of extension strings */
	int modes;
	struct codec * (*init)(const char *, int, const char *, const char *, int, int, int);
	void (*print_encodings)(const char *);
};

static const char *wav_ext[]   = { ".wav", NULL };
static const char *aiff_ext[]  = { ".aif", ".aiff", ".aifc", NULL };
static const char *au_ext[]    = { ".au", NULL };
static const char *raw_ext[]   = { ".raw", NULL };
static const char *paf_ext[]   = { ".paf", NULL };
static const char *svx_ext[]   = { ".8svx", ".iff", NULL };
static const char *nist_ext[]  = { ".nist", NULL };
static const char *voc_ext[]   = { ".voc", NULL };
static const char *ircam_ext[] = { ".sf", NULL };
static const char *w64_ext[]   = { ".w64", NULL };
static const char *mat4_ext[]  = { ".mat", NULL };
static const char *mat5_ext[]  = { ".mat", NULL };
static const char *pvf_ext[]   = { ".pvf", NULL };
static const char *xi_ext[]    = { ".xi", NULL };
static const char *htk_ext[]   = { ".htk", NULL };
static const char *sds_ext[]   = { ".sds", NULL };
static const char *avr_ext[]   = { ".avr", NULL };
static const char *wavex_ext[] = { ".wav", ".wavex", NULL };
static const char *sd2_ext[]   = { ".sd2", NULL };
static const char *flac_ext[]  = { ".flac", NULL };
static const char *caf_ext[]   = { ".caf", NULL };
static const char *wve_ext[]   = { ".wve", NULL };
static const char *ogg_ext[]   = { ".ogg", ".oga", ".ogv", NULL };
static const char *mpc2k_ext[] = { ".mpc2k", NULL };
static const char *rf64_ext[]  = { ".wav", ".rf64", NULL };
static const char *mp3_ext[]   = { ".mp3", NULL };

struct codec_info codecs[] = {
	{ "sndfile", NULL,      CODEC_MODE_READ,                  sndfile_codec_init, sndfile_codec_print_encodings },
	{ "wav",     wav_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "aiff",    aiff_ext,  CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "au",      au_ext,    CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "raw",     raw_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "paf",     paf_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "svx",     svx_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "nist",    nist_ext,  CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "voc",     voc_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "ircam",   ircam_ext, CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "w64",     w64_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "mat4",    mat4_ext,  CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "mat5",    mat5_ext,  CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "pvf",     pvf_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "xi",      xi_ext,    CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "htk",     htk_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "sds",     sds_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "avr",     avr_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "wavex",   wavex_ext, CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "sd2",     sd2_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "flac",    flac_ext,  CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "caf",     caf_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "wve",     wve_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "ogg",     ogg_ext,   CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "mpc2k",   mpc2k_ext, CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "rf64",    rf64_ext,  CODEC_MODE_READ|CODEC_MODE_WRITE, sndfile_codec_init, sndfile_codec_print_encodings },
	{ "alsa",    NULL,      CODEC_MODE_READ|CODEC_MODE_WRITE, alsa_codec_init,    alsa_codec_print_encodings },
	{ "mp3",     mp3_ext,   CODEC_MODE_READ,                  mp3_codec_init,     mp3_codec_print_encodings },
	{ "null",    NULL,      CODEC_MODE_READ|CODEC_MODE_WRITE, null_codec_init,    null_codec_print_encodings },
};

static const char *fallback_codecs[] = {
	"sndfile",
};

static struct codec_info * get_codec_info_by_type(const char *type)
{
	int i;
	for (i = 0; i < LENGTH(codecs); ++i)
		if (strcmp(type, codecs[i].type) == 0)
			return &codecs[i];
	return NULL;
}

static struct codec_info * get_codec_info_by_ext(const char *ext)
{
	int i, k;
	for (i = 0; i < LENGTH(codecs); ++i) {
		if (codecs[i].ext == NULL)
			continue;
		for (k = 0; codecs[i].ext[k] != NULL; ++k)
			if (strcasecmp(ext, codecs[i].ext[k]) == 0)
				return &codecs[i];
	}
	return NULL;
}

struct codec * init_codec(const char *type, int mode, const char *path, const char *enc, int endian, int rate, int channels)
{
	int i;
	struct codec_info *info;
	struct codec *c;
	const char *ext;
	ext = strrchr(path, '.');
	if (type == NULL && (ext == NULL || get_codec_info_by_ext(ext) == NULL) && mode == CODEC_MODE_WRITE)
		type = DEFAULT_OUTPUT_TYPE;
	if (type != NULL) {
		info = get_codec_info_by_type(type);
		if (info == NULL) {
			LOG(LL_ERROR, "dsp: error: bad type: %s\n", type);
			return NULL;
		}
		if (info->modes & mode)
			return info->init(info->type, mode, path, enc, endian, rate, channels);
		LOG(LL_ERROR, "dsp: %s: error: mode '%c' not supported\n", info->type, (mode == CODEC_MODE_READ) ? 'r' : 'w');
		return NULL;
	}
	if (ext != NULL && (info = get_codec_info_by_ext(ext)) != NULL) {
		if (info->modes & mode)
			return info->init(info->type, mode, path, enc, endian, rate, channels);
		LOG(LL_ERROR, "dsp: %s: error: mode '%c' not supported\n", info->type, (mode == CODEC_MODE_READ) ? 'r' : 'w');
		return NULL;
	}
	for (i = 0; i < LENGTH(fallback_codecs); ++i) {
		info = get_codec_info_by_type(fallback_codecs[i]);
		if (info != NULL && info->modes & mode && (c = info->init(info->type, mode, path, enc, endian, rate, channels)) != NULL)
			return c;
	}
	return NULL;
}

void destroy_codec(struct codec *c)
{
	c->destroy(c);
	free(c);
}

void append_codec(struct codec_list *l, struct codec *c)
{
	if (l->tail == NULL)
		l->head = c;
	else
		l->tail->next = c;
	l->tail = c;
	c->next = NULL;
}

void destroy_codec_list_head(struct codec_list *l)
{
	struct codec *h = l->head;
	if (h == NULL)
		return;
	l->head = h->next;
	destroy_codec(h);
}

void destroy_codec_list(struct codec_list *l)
{
	while (l->head != NULL)
		destroy_codec_list_head(l);
}

void print_all_codecs(void)
{
	int i;
	fprintf(stderr, "types:\n  type:    modes: encodings:\n");
	for (i = 0; i < LENGTH(codecs); ++i) {
		fprintf(stderr, "  %-8s %c%c    ", codecs[i].type, (codecs[i].modes & CODEC_MODE_READ) ? 'r' : ' ', (codecs[i].modes & CODEC_MODE_WRITE) ? 'w' : ' ');
		codecs[i].print_encodings(codecs[i].type);
		fputc('\n', stderr);
	}
}