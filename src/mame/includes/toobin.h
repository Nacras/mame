// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*************************************************************************

    Atari Toobin' hardware

*************************************************************************/
#ifndef MAME_INCLUDES_TOOBIN_H
#define MAME_INCLUDES_TOOBIN_H

#pragma once

#include "machine/atarigen.h"
#include "audio/atarijsa.h"
#include "video/atarimo.h"

class toobin_state : public atarigen_state
{
public:
	toobin_state(const machine_config &mconfig, device_type type, const char *tag) :
		atarigen_state(mconfig, type, tag),
		m_jsa(*this, "jsa"),
		m_playfield_tilemap(*this, "playfield"),
		m_alpha_tilemap(*this, "alpha"),
		m_mob(*this, "mob"),
		m_interrupt_scan(*this, "interrupt_scan"),
		m_sound_int_state(0)
	{ }

	void toobin(machine_config &config);

protected:
	virtual void machine_start() override;
	virtual void video_start() override;
	virtual void update_interrupts() override;

	DECLARE_WRITE_LINE_MEMBER(sound_int_write_line);

	DECLARE_WRITE16_MEMBER(interrupt_scan_w);
	DECLARE_WRITE16_MEMBER(paletteram_w);
	DECLARE_WRITE16_MEMBER(intensity_w);
	DECLARE_WRITE16_MEMBER(xscroll_w);
	DECLARE_WRITE16_MEMBER(yscroll_w);
	DECLARE_WRITE16_MEMBER(slip_w);

	TILE_GET_INFO_MEMBER(get_alpha_tile_info);
	TILE_GET_INFO_MEMBER(get_playfield_tile_info);

	uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	void main_map(address_map &map);

private:
	required_device<atari_jsa_i_device> m_jsa;
	required_device<tilemap_device> m_playfield_tilemap;
	required_device<tilemap_device> m_alpha_tilemap;
	required_device<atari_motion_objects_device> m_mob;

	required_shared_ptr<uint16_t> m_interrupt_scan;

	double          m_brightness;
	bitmap_ind16 m_pfbitmap;

	uint8_t               m_sound_int_state;

	static const atari_motion_objects_config s_mob_config;
};

#endif // MAME_INCLUDES_TOOBIN_H
