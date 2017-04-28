#include "gdal.h"
#include "ogr_api.h"
#include "ogrsf_frmts.h"
#include "gdal_priv.h"
#include "ogr_geometry.h"
#include "cpl_error.h"
#include <iostream>

#define CHECK_CPL_ERROR(num) \
    num = CPLGetLastErrorNo(); \
    if (num != CPLE_None) \
    { \
        std::cerr << "Last operation was not successful (" << num << ")" << std::endl; \
        return 1; \
    }

int main(int argc, char** argv)
{
    OGRRegisterAll();
    GDALAllRegister();

    int errNo = CPLE_None;
    int gdalCount = 0;
    int ogrCount = 0;

    // Print GDAL driver support
    GDALDriverManager* drvManager = GetGDALDriverManager();
    if (drvManager)
    {
        int driverCount = drvManager->GetDriverCount();
        for (int i = 0; i < driverCount; i++)
        {
            GDALDriver* driver = drvManager->GetDriver(i);
            if (driver)
            {
                std::string drvInfo;
                const char* desc = driver->GetDescription();
                if (desc && strlen(desc) > 0)
                {
                    drvInfo += "Description: ";
                    drvInfo += desc;
                    drvInfo += " ";
                }
                const char* ext = driver->GetMetadataItem(GDAL_DMD_EXTENSION);
                if (ext && strlen(ext) > 0)
                {
                    drvInfo += "Extension: ";
                    drvInfo += ext;
                    drvInfo += " ";
                }
                std::cout << "GDAL Driver - " << drvInfo << std::endl;
                gdalCount++;
            }
        }
    }

    // Print OGR driver support
    OGRSFDriverRegistrar* ogrRegistrar = OGRSFDriverRegistrar::GetRegistrar();
    if (ogrRegistrar)
    {
        int driverCount = ogrRegistrar->GetDriverCount();
        for (int i = 0; i < driverCount; i++)
        {
            OGRSFDriver* driver = ogrRegistrar->GetDriver(i);
            if (driver)
            {
                std::string drvInfo;
                const char* desc = driver->GetName();
                if (desc && strlen(desc) > 0)
                {
                    drvInfo += "Name: ";
                    drvInfo += desc;
                    drvInfo += " ";
                }
                std::cout << "OGR Driver - " << drvInfo << std::endl;
                ogrCount++;
            }
        }
    }
    std::cout << gdalCount << " GDAL Drivers found" << std::endl;
    std::cout << ogrCount << " OGR Drivers found" << std::endl;

    std::string wkt1 = "POLYGON((0 0, 10 10, 10 0, 0 0))";
    std::string wkt2 = "POLYGON((-90 -90, -90 90, 190 -90, -90 -90))";

    char* cwkt1 = (char *)wkt1.c_str();
    char* cwkt2 = (char *)wkt2.c_str();

    OGRGeometry* geom1 = NULL;
    OGRGeometry* geom2 = NULL;
    OGRSpatialReference osr;
    OGRErr err = OGRGeometryFactory::createFromWkt(&cwkt1, &osr, &geom1);
    if (err != OGRERR_NONE)
    {
        std::cerr << "Error creating geometry 1 from WKT (" << err << ")" << std::endl;
        if (NULL != geom1)
            OGRGeometryFactory::destroyGeometry(geom1);
        return 1;
    }
    if (geom1 == NULL)
    {
        std::cerr << "Could not create geometry 1 from WKT" << std::endl;
        return 1;
    }
    std::cout << "Made geometry 1 from WKT" << std::endl;

    err = OGRGeometryFactory::createFromWkt(&cwkt2, &osr, &geom2);
    if (err != OGRERR_NONE)
    {
        std::cerr << "Error creating geometry 2 from WKT (" << err << ")" << std::endl;
        if (NULL != geom1)
            OGRGeometryFactory::destroyGeometry(geom1);
        if (NULL != geom2)
            OGRGeometryFactory::destroyGeometry(geom2);
        return 1;
    }
    if (geom2 == NULL)
    {
        std::cerr << "Could not create geometry 2 from WKT" << std::endl;
        if (NULL != geom1)
            OGRGeometryFactory::destroyGeometry(geom1);
        return 1;
    }
    std::cout << "Made geometry 2 from WKT" << std::endl;

    // This should verify GEOS support

    bool bContains = geom1->Contains(geom2);
    CHECK_CPL_ERROR(errNo)
    std::cout << "Contains result: " << bContains << std::endl;

    if (NULL != geom1)
        OGRGeometryFactory::destroyGeometry(geom1);
    if (NULL != geom2)
        OGRGeometryFactory::destroyGeometry(geom2);

    GDALDestroyDriverManager();
    OGRCleanupAll();

    return 0;
}