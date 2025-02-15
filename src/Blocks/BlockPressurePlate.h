
#pragma once

#include "BlockHandler.h"
#include "BlockSlab.h"
#include "../Chunk.h"
#include "BlockStairs.h"




class cBlockPressurePlateHandler final :
	public cClearMetaOnDrop<cBlockHandler>
{
	using Super = cClearMetaOnDrop<cBlockHandler>;

public:

	using Super::Super;

private:

	virtual bool CanBeAt(const cChunk & a_Chunk, const Vector3i a_Position, const NIBBLETYPE a_Meta) const override
	{
		const auto PosBelow = a_Position.addedY(-1);
		if (!cChunkDef::IsValidHeight(PosBelow))
		{
			return false;
		}

		BLOCKTYPE Block;
		NIBBLETYPE BlockMeta;
		a_Chunk.GetBlockTypeMeta(PosBelow, Block, BlockMeta);

		// upside down slabs
		if (cBlockSlabHandler::IsAnySlabType(Block))
		{
			return BlockMeta & E_META_WOODEN_SLAB_UPSIDE_DOWN;
		}

		// upside down stairs
		if (cBlockStairsHandler::IsAnyStairType(Block))
		{
			return BlockMeta & E_BLOCK_STAIRS_UPSIDE_DOWN;
		}

		switch (Block)
		{
			case E_BLOCK_ACACIA_FENCE:
			case E_BLOCK_BIRCH_FENCE:
			case E_BLOCK_DARK_OAK_FENCE:
			case E_BLOCK_FENCE:
			case E_BLOCK_HOPPER:
			case E_BLOCK_JUNGLE_FENCE:
			case E_BLOCK_NETHER_BRICK_FENCE:
			case E_BLOCK_SPRUCE_FENCE:
			{
				return true;
			}
			default:
			{
				return !cBlockInfo::IsTransparent(Block);
			}
		}
	}





	virtual ColourID GetMapBaseColourID(NIBBLETYPE a_Meta) const override
	{
		UNUSED(a_Meta);
		switch (m_BlockType)
		{
			case E_BLOCK_STONE_PRESSURE_PLATE: return 11;
			case E_BLOCK_WOODEN_PRESSURE_PLATE: return 13;
			case E_BLOCK_HEAVY_WEIGHTED_PRESSURE_PLATE: return 6;
			case E_BLOCK_LIGHT_WEIGHTED_PRESSURE_PLATE: return 30;
			default:
			{
				ASSERT(!"Unhandled blocktype in pressure plate handler!");
				return 0;
			}
		}
	}
} ;




