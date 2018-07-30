#pragma once
#include "../SubWindowWithBorder.h"
namespace ItemSystem
{
	enum class Rarity
	{
		Common = static_cast<int>(SubWindowWithBorder::Colour::Green),
		Rare = static_cast<int>(SubWindowWithBorder::Colour::Yellow),
		Ledgendary = static_cast<int>(SubWindowWithBorder::Colour::Purple)
	};
}
