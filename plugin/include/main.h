#ifndef		MAIN_H
#define		MAIN_H

#include    <osg/Geometry>
#include    <osg/Geode>
#include    <osgDB/FileNameUtils>
#include    <osgDB/FileUtils>
#include    <osgDB/Registry>
#include    <osgUtil/SmoothingVisitor>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct face_t
{
    std::vector<unsigned int> indices;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct pmd_mesh_t
{
    osg::ref_ptr<osg::Vec3Array> vertices;
    osg::ref_ptr<osg::Vec3Array> normals;
    std::vector<face_t> faces;

    pmd_mesh_t()
        : vertices(new osg::Vec3Array)
        , normals(new osg::Vec3Array)
    {

    }

    osg::Vec3 calcFaceNormal(const face_t &face) const
    {
        osg::Vec3 v0 = (*vertices)[face.indices[0]];
        osg::Vec3 v1 = (*vertices)[face.indices[1]];
        osg::Vec3 v2 = (*vertices)[face.indices[2]];

        osg::Vec3 n = (v1 - v0) ^ (v2 - v0);

        return n * (1 / n.length());
    }
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ReaderWriterPMD : public osgDB::ReaderWriter
{
public:

    ReaderWriterPMD();

    virtual ReadResult readNode(const std::string &filename,
                                const osgDB::Options *options) const;

    virtual ReadResult readNode(std::istream &stream,
                                const osgDB::Options *options) const;

private:

    pmd_mesh_t parsePMD(std::istream &stream) const;

    std::vector<std::string> parseLine(const std::string &line) const;
};

#endif
