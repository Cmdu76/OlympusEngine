#include "Map.hpp"
#include "World.hpp"

namespace oe
{

Map::Map(World& world)
	: Entity(world)
	, mName("")
	, mTileset(nullptr)
	, mSize()
	, mTileSize()
	, mOrientation(MapUtility::Orientation::Orthogonal)
	, mStaggerAxis(MapUtility::StaggerAxis::Y)
	, mStaggerIndex(MapUtility::StaggerIndex::Odd)
	, mHexSideLength(0)
{
}

Map::~Map()
{
}

std::vector<Vector2i> Map::getNeighboors(const Vector2i& coords, bool diag)
{
	return MapUtility::getNeighboors(coords, mOrientation, diag, mStaggerIndex, mStaggerAxis);
}

Vector2i Map::worldToCoords(const Vector2& world)
{
	return MapUtility::worldToCoords(world - getPosition(), mOrientation, mTileSize, mStaggerIndex, mStaggerAxis, mHexSideLength);
}

Vector2 Map::coordsToWorld(const Vector2i& coords)
{
	return MapUtility::coordsToWorld(coords, mOrientation, mTileSize, mStaggerIndex, mStaggerAxis, mHexSideLength) + getPosition();
}

LayerComponent& Map::addLayer()
{
	mLayers.emplace_back(*this);
	mLayers.back().create(mTileset, mSize, mTileSize, mOrientation, mStaggerAxis, mStaggerIndex, mHexSideLength);
	if (isPlaying())
	{
		mLayers.back().onSpawn();
	}
	return mLayers.back();
}

const std::string& Map::getName() const
{
	return mName;
}

void Map::setName(const std::string& name)
{
	mName = name;
}

Tileset* Map::getTileset() const
{
	return mTileset;
}

void Map::setTileset(Tileset* tileset)
{
	mTileset = tileset;
}

const Vector2i& Map::getSize() const
{
	return mSize;
}

void Map::setSize(const Vector2i& size)
{
	mSize = size;
}

const Vector2i& Map::getTileSize() const
{
	return mTileSize;
}

void Map::setTileSize(const Vector2i& tileSize)
{
	mTileSize = tileSize;
}

MapUtility::Orientation Map::getOrientation() const
{
	return mOrientation;
}

void Map::setOrientation(MapUtility::Orientation orientation)
{
	mOrientation = orientation;
}

MapUtility::StaggerAxis Map::getStaggerAxis() const
{
	return mStaggerAxis;
}

void Map::setStaggerAxis(MapUtility::StaggerAxis axis)
{
	mStaggerAxis = axis;
}

MapUtility::StaggerIndex Map::getStaggerIndex() const
{
	return mStaggerIndex;
}

void Map::setStaggerIndex(MapUtility::StaggerIndex index)
{
	mStaggerIndex = index;
}

U32 Map::getHexSizeLength() const
{
	return mHexSideLength;
}

void Map::setHexSideLength(U32 hexSideLength)
{
	mHexSideLength = hexSideLength;
}

} // namespace ke