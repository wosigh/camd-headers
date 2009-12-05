/****************************************************************/
/****************************************************************/
#ifndef _PALMOMXJPEGENCEXIF_H
#define _PALMOMXJPEGENCEXIF_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define                 TXF_SIZE        (3*256)
// imageData validity masks

#define IMG_ORIEN_MASK          ((unsigned int)(0x01 << 0))
#define IMG_MAKE_MASK           ((unsigned int)(0x01 << 1))
#define IMG_MODEL_MASK          ((unsigned int)(0x01 << 2))
#define IMG_ARTIST_MASK         ((unsigned int)(0x01 << 3))
#define IMG_IMGDES_MASK         ((unsigned int)(0x01 << 4))
#define IMG_DATE_MASK           ((unsigned int)(0x01 << 5))

// gpsData Validity mask
//
#define GPS_VER_MASK            ((unsigned int)(0x01 << 0))
#define GPS_LATREF_MASK         ((unsigned int)(0x01 << 1))
#define GPS_LAT_MASK            ((unsigned int)(0x01 << 2))
#define GPS_LONGREF_MASK        ((unsigned int)(0x01 << 3))
#define GPS_LONG_MASK           ((unsigned int)(0x01 << 4))
#define GPS_ALTREF_MASK         ((unsigned int)(0x01 << 5))
#define GPS_ALT_MASK            ((unsigned int)(0x01 << 6))
#define GPS_STAT_MASK           ((unsigned int)(0x01 << 7))
#define GPS_MES_MASK            ((unsigned int)(0x01 << 8))
#define GPS_DOPF_MASK           ((unsigned int)(0x01 << 9))
// Phot data validity mask
#define IMG_XRES_MASK           ((unsigned int)(0x01 << 0))
#define IMG_YRES_MASK           ((unsigned int)(0x01 << 1))
#define IMG_RESU_MASK           ((unsigned int)(0x01 << 2))
#define IMG_TXF_MASK            ((unsigned int)(0x01 << 3))
#define IMG_YCBCR_MASK          ((unsigned int)(0x01 << 4))
#define IMG_YCBCRCOF_MASK       ((unsigned int)(0x01 << 5))
#define IMG_EXPTIM_MASK         ((unsigned int)(0x01 << 6))
#define IMG_VER_MASK            ((unsigned int)(0x01 << 7))
#define IMG_COMP_MASK           ((unsigned int)(0x01 << 8))
#define IMG_FLASH_MASK          ((unsigned int)(0x01 << 9))
#define IMG_FLASHPIX_MASK       ((unsigned int)(0x01 << 10))
#define IMG_COLSPCE_MASK        ((unsigned int)(0x01 << 11))
#define IMG_PIXX_MASK           ((unsigned int)(0x01 << 12))
#define IMG_PIXY_MASK           ((unsigned int)(0x01 << 13))
#define IMG_EXP_MASK            ((unsigned int)(0x01 << 14))
#define IMG_WHTBAL_MASK         ((unsigned int)(0x01 << 15))
#define IMG_APPVAL_MASK         ((unsigned int)(0x01 << 16))
#define IMG_FOCLN_MASK          ((unsigned int)(0x01 << 17))
#define IMG_FNUMBR_MASK         ((unsigned int)(0x01 << 18))
#define IMG_EXPPROG_MASK        ((unsigned int)(0x01 << 19))

typedef enum {
        /* NOTE: only handling the specific orientations handed to the
             jpeg encoder via the application.  Not covering the full
             EXIF 2.1 spec concerning orientation field. */
        EXIF_0_DEG_ORIENTATION   = 1, /* normal  */
        EXIF_90_DEG_ORIENTATION  = 6,
        EXIF_180_DEG_ORIENTATION = 3,
        EXIF_270_DEG_ORIENTATION = 8,
} exif_orientation_t;

//Operations
//
#define IS_VALID(x, mask)       ((x & mask) == mask)
#define DO_VALID(x, mask)       (x |= mask)
#define DO_INVALID(x, mask)     (x &= ~mask)

/* Structure of the EXIF data send by the application */

/* Data related to image tag */
typedef struct   {
        unsigned short  Orientation;
        char*           Make;
        char*           Model;
        char*           Artist;
        char*           ImageDescription;
        char            DateTime[20];
        unsigned int    valid;
} imageData;

/* data related to GPS tag */

typedef struct {
        unsigned char   VersionID[4];
        char            LatitudeRef[2];
        unsigned int    Latitude[6];
        char            LongitudeRef[2];
        unsigned int    Longitude[6];
        unsigned char   AltitudeRef;
        unsigned int    Altitude[2];
        char            Status[2];
        char            MeasureMode[2];
        unsigned int    DOP[2];
        unsigned int    valid;
} gpsData;

typedef struct {
        unsigned int    XResolution[2];
        unsigned int    YResolution[2];
        unsigned short  ResolutionUnit;
        unsigned short  TransferFunction[TXF_SIZE];
        unsigned short  YCbCrPositioning;
        unsigned int    YCbCrCoefficients[6];
        unsigned int    ExposureTime[2];
        unsigned int    FNumber[2];
        unsigned short  ExposureProgram;
        unsigned int    ApertureValue[2];
        unsigned int    FocalLength[2];
        unsigned char   ExifVersion[4];
        unsigned char   ComponentsConfiguration[4];
        unsigned short  Flash;
        unsigned char   FlashpixVersion[4];
        unsigned short  ColorSpace;
        unsigned int    PixelXDimension;
        unsigned int    PixelYDimension;
        unsigned short  ExposureMode;
        unsigned short  WhiteBalance;
        unsigned int    valid;
} photoData;

typedef struct {
        photoData       exif;
        guint8*         buffer;
}ImageBuffer;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

 