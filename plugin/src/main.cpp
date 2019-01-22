#include	"main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ReaderWriterPMD::ReaderWriterPMD()
{
    supportsExtension("pmd", "PMD model file");
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osgDB::ReaderWriter::ReadResult ReaderWriterPMD::readNode(
        const std::string &filename,
        const osgDB::Options *options) const
{
    std::string ext = osgDB::getLowerCaseFileExtension(filename);

    if (!acceptsExtension(ext))
        return ReadResult::FILE_NOT_HANDLED;

    std::string fileName = osgDB::findDataFile(filename, options);

    if (fileName.empty())
        return ReadResult::FILE_NOT_FOUND;

    std::ifstream stream(fileName.c_str(), std::ios::in);

    if (!stream)
        return ReadResult::ERROR_IN_READING_FILE;

    return readNode(stream, options);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osgDB::ReaderWriter::ReadResult ReaderWriterPMD::readNode(
        std::istream &stream,
        const osgDB::Options *options) const
{
    (void) options;

    pmd_mesh_t mesh = parsePMD(stream);

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(mesh.vertices.get());

    for (size_t i = 0; i < mesh.faces.size(); ++i)
    {
        osg::ref_ptr<osg::DrawElementsUInt> polygon = new osg::DrawElementsUInt(osg::PrimitiveSet::POLYGON, 0);

        for (size_t j = 0; j < mesh.faces[i].indices.size(); ++j)
            polygon->push_back(mesh.faces[i].indices[j]);

        geom->addPrimitiveSet(polygon.get());
    }

    geom->setNormalArray(mesh.normals.get());
    geom->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom.get());

    return geode.release();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
pmd_mesh_t ReaderWriterPMD::parsePMD(std::istream &stream) const
{
    pmd_mesh_t mesh;

    while (!stream.eof())
    {
        std::string line;
        std::getline(stream, line);
        std::vector<std::string> tokens = parseLine(line);

        if (tokens[0] == "vertex")
        {
            osg::Vec3 point;
            std::istringstream iss(tokens[1]);
            iss >> point.x() >> point.y() >> point.z();
            mesh.vertices->push_back(point);
        }

        if (tokens[0] == "face")
        {
            unsigned int idx = 0;
            std::istringstream iss(tokens[1]);
            face_t face;

            while (!iss.eof())
            {
                iss >> idx;
                face.indices.push_back(idx);
            }

            mesh.faces.push_back(face);
            mesh.normals->push_back(mesh.calcFaceNormal(face));
        }
    }

    return mesh;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string delete_symbol(const std::string &str, char symbol)
{
    std::string tmp = str;
    tmp.erase(std::remove(tmp.begin(), tmp.end(), symbol), tmp.end());
    return tmp;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::vector<std::string> ReaderWriterPMD::parseLine(const std::string &line) const
{
    std::vector<std::string> tokens;
    std::string tmp = delete_symbol(line, '\r');

    size_t pos = 0;
    std::string token;

    while ( (pos = tmp.find(':')) != std::string::npos )
    {
       token = tmp.substr(0, pos);
       tmp.erase(0, pos + 1);

       if (!token.empty())
           tokens.push_back(token);
    }

    tokens.push_back(tmp);

    return tokens;
}

REGISTER_OSGPLUGIN( pmd, ReaderWriterPMD )
