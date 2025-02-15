
#pragma once

#include "BlockHandler.h"





class cBlockPortalHandler final :
	public cBlockHandler
{
	using Super = cBlockHandler;

public:

	using Super::Super;

private:

	virtual cItems ConvertToPickups(const NIBBLETYPE a_BlockMeta, const cItem * const a_Tool) const override
	{
		// No pickups
		return {};
	}





	virtual void OnUpdate(
		cChunkInterface & a_ChunkInterface,
		cWorldInterface & a_WorldInterface,
		cBlockPluginInterface & a_PluginInterface,
		cChunk & a_Chunk,
		const Vector3i a_RelPos
	) const override
	{
		// Spawn zombie pigmen with a 0.05% chance:
		if (GetRandomProvider().RandBool(0.9995))
		{
			return;
		}
		auto WorldPos = a_Chunk.RelativeToAbsolute(a_RelPos);
		a_WorldInterface.SpawnMob(WorldPos.x, WorldPos.y, WorldPos.z, mtZombiePigman, false);
	}





	virtual bool CanBeAt(const cChunk & a_Chunk, const Vector3i a_Position, const NIBBLETYPE a_Meta) const override
	{
		if (!cChunkDef::IsValidHeight(a_Position.addedY(-1)) || !cChunkDef::IsValidHeight(a_Position.addedY(1)))
		{
			return false;  // Must be 1 away from the boundary, there will always be another portal or an obsidian between the portal block and the boundary.
		}

		switch (a_Meta)
		{
			case 0x1:
			{
				static const std::array<Vector3i, 4> PortalCheck
				{
					{
						{ 0, 1, 0 },
						{ 0, -1, 0 },
						{ 1, 0, 0 },
						{ -1, 0, 0 },
					}
				};

				for (const auto & Direction : PortalCheck)
				{
					BLOCKTYPE Block;
					a_Chunk.UnboundedRelGetBlockType(a_Position + Direction, Block);
					if ((Block != E_BLOCK_NETHER_PORTAL) && (Block != E_BLOCK_OBSIDIAN))
					{
						return false;
					}
				}
				break;
			}
			case 0x2:
			{
				static const std::array<Vector3i, 4> PortalCheck
				{
					{
						{ 0, 1, 0 },
						{ 0, -1, 0 },
						{ 0, 0, -1 },
						{ 0, 0, 1 },
					}
				};

				for (const auto & Direction : PortalCheck)
				{
					BLOCKTYPE Block;
					a_Chunk.UnboundedRelGetBlockType(a_Position + Direction, Block);
					if ((Block != E_BLOCK_NETHER_PORTAL) && (Block != E_BLOCK_OBSIDIAN))
					{
						return false;
					}
				}
				break;
			}
		}
		return true;
	}





	virtual ColourID GetMapBaseColourID(NIBBLETYPE a_Meta) const override
	{
		UNUSED(a_Meta);
		return 24;
	}
} ;




