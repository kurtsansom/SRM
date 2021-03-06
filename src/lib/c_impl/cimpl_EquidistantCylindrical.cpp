// SRM SDK Release 4.1.4 - July 1, 2011

// - SRM spec. 4.1

/*
 *                             NOTICE
 * 
 * This software is provided openly and freely for use in representing and
 * interchanging environmental data & databases.
 * 
 * This software was developed for use by the United States Government with
 * unlimited rights.  The software was developed under contract
 * DASG60-02-D-0006 TO-193 by Science Applications International Corporation.
 * The software is unclassified and is deemed as Distribution A, approved
 * for Public Release.
 * 
 * Use by others is permitted only upon the ACCEPTANCE OF THE TERMS AND
 * CONDITIONS, AS STIPULATED UNDER THE FOLLOWING PROVISIONS:
 * 
 *    1. Recipient may make unlimited copies of this software and give
 *       copies to other persons or entities as long as the copies contain
 *       this NOTICE, and as long as the same copyright notices that
 *       appear on, or in, this software remain.
 * 
 *    2. Trademarks. All trademarks belong to their respective trademark
 *       holders.  Third-Party applications/software/information are
 *       copyrighted by their respective owners.
 * 
 *    3. Recipient agrees to forfeit all intellectual property and
 *       ownership rights for any version created from the modification
 *       or adaptation of this software, including versions created from
 *       the translation and/or reverse engineering of the software design.
 * 
 *    4. Transfer.  Recipient may not sell, rent, lease, or sublicense
 *       this software.  Recipient may, however enable another person
 *       or entity the rights to use this software, provided that this
 *       AGREEMENT and NOTICE is furnished along with the software and
 *       /or software system utilizing this software.
 * 
 *       All revisions, modifications, created by the Recipient, to this
 *       software and/or related technical data shall be forwarded by the
 *       Recipient to the Government at the following address:
 * 
 *         SMDC
 *         Attention SEDRIS (TO193) TPOC
 *         P.O. Box 1500
 *         Huntsville, AL  35807-3801
 * 
 *         or via electronic mail to:  se-mgmt@sedris.org
 * 
 *    5. No Warranty. This software is being delivered to you AS IS
 *       and there is no warranty, EXPRESS or IMPLIED, as to its use
 *       or performance.
 * 
 *       The RECIPIENT ASSUMES ALL RISKS, KNOWN AND UNKNOWN, OF USING
 *       THIS SOFTWARE.  The DEVELOPER EXPRESSLY DISCLAIMS, and the
 *       RECIPIENT WAIVES, ANY and ALL PERFORMANCE OR RESULTS YOU MAY
 *       OBTAIN BY USING THIS SOFTWARE OR DOCUMENTATION.  THERE IS
 *       NO WARRANTY, EXPRESS OR, IMPLIED, AS TO NON-INFRINGEMENT OF
 *       THIRD PARTY RIGHTS, MERCHANTABILITY, OR FITNESS FOR ANY
 *       PARTICULAR PURPOSE.  IN NO EVENT WILL THE DEVELOPER, THE
 *       UNITED STATES GOVERNMENT OR ANYONE ELSE ASSOCIATED WITH THE
 *       DEVELOPMENT OF THIS SOFTWARE BE HELD LIABLE FOR ANY CONSEQUENTIAL,
 *       INCIDENTAL OR SPECIAL DAMAGES, INCLUDING ANY LOST PROFITS
 *       OR LOST SAVINGS WHATSOEVER.
 */


#include "srm.h"
#include "cimpl_EquidistantCylindrical.hpp"
#include "cimpl_BaseSRF.hpp"
#include "cimpl_BaseSRF3D.hpp"
#include "cimpl_BaseSRFwithEllipsoidalHeight.hpp"
#include "cimpl_BaseMapProjection.hpp"
#include "srm_level_0_int_types.hpp"

extern "C"
{

SRM_Status_Code cimpl_SRM_EC_GetSRFParameters
(
    SRM_Object_Reference  this_object,
    SRM_EC_Parameters    *parameters /* OUT */
)
{
    if (this_object == 0 || parameters  == 0)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;
    SRM_SRF srf = (SRM_SRF)((SRM_BaseWrapper *)this_object)->state;

    if (!VALID_SRF_HANDLE(srf))
    {
        status = SRM_STATCOD_INVALID_INPUT;
    }
    else if (!INT_SRF(srf)->isA(BaseSRF::SRF_TYP_EC))
    {
        status = SRM_STATCOD_INVALID_SOURCE_SRF;
    }
    else
    {
        try
        {
           *parameters =
               ((SRF_EquidistantCylindrical *)INT_SRF(srf))->getSRFParameters();
        }
        catch (Exception e)
        {
            status = e.getCode();
        }
    }
    return status;
}


SRM_Status_Code SRM_EC_Create
(
          SRM_ORM_Code                orm_code,
          SRM_RT_Code                 rt_code,
    const SRM_EC_Parameters          *parameters,
          SRM_EquidistantCylindrical *new_srf  /* OUT */
)
{
    if (!new_srf)
    {
        return SRM_STATCOD_INVALID_INPUT;
    }
    else if ((new_srf->methods = new SRM_EC_Method_List)==0)
    {
        return SRM_STATCOD_MEMORY_ALLOCATION_ERROR;
    }
    new_srf->methods->AssociateSurfaceCoordinate          = &cimpl_SRM_AssociateSurfaceCoordinateEH;
    new_srf->methods->ChangeCoordinate3DSRF               = &cimpl_SRM_ChangeCoordinate3DSRF;
    new_srf->methods->ChangeCoordinate3DArraySRF          = &cimpl_SRM_ChangeCoordinate3DArraySRF;
    new_srf->methods->ChangeCoordinate3DArraySRFObject    = &cimpl_SRM_ChangeCoordinate3DArraySRFObject;
    new_srf->methods->ChangeCoordinate3DSRFObject         = &cimpl_SRM_ChangeCoordinate3DSRFObject;
    new_srf->methods->ChangeDirectionArraySRF             = &cimpl_SRM_ChangeDirectionArraySRF;
    new_srf->methods->ChangeDirectionSRF                  = &cimpl_SRM_ChangeDirectionSRF;
    new_srf->methods->ChangeOrientationSRF                = &cimpl_SRM_ChangeOrientationSRF;
    new_srf->methods->ChangeDirectionArraySRFObject       = &cimpl_SRM_ChangeDirectionArraySRFObject;
    new_srf->methods->ChangeOrientationSRFObject          = &cimpl_SRM_ChangeOrientationSRFObject;
    new_srf->methods->ChangeDirectionSRFObject            = &cimpl_SRM_ChangeDirectionSRFObject;
    new_srf->methods->ConvergenceOfTheMeridian            = &cimpl_SRM_ConvergenceOfTheMeridian;
    new_srf->methods->CreateCoordinate3D                  = &cimpl_SRM_CreateCoordinate3D;
    new_srf->methods->CreateDirection                     = &cimpl_SRM_CreateDirection;
    new_srf->methods->CreateOrientation                   = &cimpl_SRM_CreateOrientation;
    new_srf->methods->CreateLocalTangentSpaceEuclideanSRF = &cimpl_SRM_CreateLocalTangentSpaceEuclideanSRF;
    new_srf->methods->CreateSurfaceCoordinate             = &cimpl_SRM_CreateSurfaceCoordinateEH;
    new_srf->methods->Destroy                             = &cimpl_SRM_Destroy;
    new_srf->methods->DestroyCoordinate3D                 = &cimpl_SRM_DestroyCoordinate3D;
    new_srf->methods->DestroyDirection                    = &cimpl_SRM_DestroyDirection;
    new_srf->methods->DestroyOrientation                  = &cimpl_SRM_DestroyOrientation;
    new_srf->methods->DestroySurfaceCoordinate            = &cimpl_SRM_DestroySurfaceCoordinateEH;
    new_srf->methods->EuclideanDistance3D                 = &cimpl_SRM_EuclideanDistance3D;
    new_srf->methods->EuclideanDistanceEH                 = &cimpl_SRM_EuclideanDistanceEH;
    new_srf->methods->GeodesicDistance                    = &cimpl_SRM_GeodesicDistance;
    new_srf->methods->GetCoordinate3DValues               = &cimpl_SRM_GetCoordinate3DValues;
    new_srf->methods->GetCSCode                           = &cimpl_SRM_GetCSCode;
    new_srf->methods->GetA                                = &cimpl_SRM_GetA;
    new_srf->methods->GetF                                = &cimpl_SRM_GetF;
    new_srf->methods->GetDirectionValues                  = &cimpl_SRM_GetDirectionValues;
    new_srf->methods->GetExtendedValidGeodeticRegion      = &cimpl_SRM_GetExtendedValidGeodeticRegion;
    new_srf->methods->GetExtendedValidRegion              = &cimpl_SRM_GetExtendedValidRegion;
    new_srf->methods->GetNaturalSRFSMemberCode            = &cimpl_SRM_GetNaturalSRFSMemberCode;
    new_srf->methods->GetOrientationValues                = &cimpl_SRM_GetOrientationValues;
    new_srf->methods->GetORMCodes                         = &cimpl_SRM_GetORMCodes;
    new_srf->methods->GetSRFCodes                         = &cimpl_SRM_GetSRFCodes;
    new_srf->methods->GetSRFParameters                    = &cimpl_SRM_EC_GetSRFParameters;
    new_srf->methods->GetSurfaceCoordinateValues          = &cimpl_SRM_GetSurfaceCoordinateValuesEH;
    new_srf->methods->GetValidGeodeticRegion              = &cimpl_SRM_GetValidGeodeticRegion;
    new_srf->methods->GetValidRegion                      = &cimpl_SRM_GetValidRegion;
    new_srf->methods->MapAzimuth                          = &cimpl_SRM_MapAzimuth;
    new_srf->methods->PromoteSurfaceCoordinate            = &cimpl_SRM_PromoteSurfaceCoordinateEH;
    new_srf->methods->PointDistortion                     = &cimpl_SRM_PointDistortion;
    new_srf->methods->SetCoordinate3DValues               = &cimpl_SRM_SetCoordinate3DValues;
    new_srf->methods->SetExtendedValidGeodeticRegion      = &cimpl_SRM_SetExtendedValidGeodeticRegion;
    new_srf->methods->SetExtendedValidRegion              = &cimpl_SRM_SetExtendedValidRegion;
    new_srf->methods->SetValidGeodeticRegion              = &cimpl_SRM_SetValidGeodeticRegion;
    new_srf->methods->SetValidRegion                      = &cimpl_SRM_SetValidRegion;
    new_srf->methods->VerticalOffset                      = &cimpl_SRM_VerticalOffset;

    SRM_SRF srf = new SRF_Wrapper;
    SRM_Status_Code status = SRM_STATCOD_SUCCESS;

    if (srf != 0)
    {
        try
        {
            INT_SRF(srf) = SRF_EquidistantCylindrical::create(orm_code,
                                                              rt_code,
                                                              *parameters);

            ((SRF_Wrapper *)srf)->_magic_number = SRM_SRF_MAGIC_NUMBER;
            new_srf->state = (void *)srf;
        }
        catch (Exception e)
        {
            delete (SRF_Wrapper *)srf;
            srf    = 0;
            status = e.getCode();
        }
    }
    else
    {
        status = SRM_STATCOD_MEMORY_ALLOCATION_ERROR;
    }
    return status;
}

}    // end Extern "C"
