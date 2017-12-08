//
//   Project Name:        Kratos
//   Last Modified by:    $Author: hbui $
//   Date:                $Date: 8 Nov 2017 $
//   Revision:            $Revision: 1.0 $
//
//

#if !defined(KRATOS_ISOGEOMETRIC_APPLICATION_MULTIPATCH_REFINEMENT_UTILITY_H_INCLUDED )
#define  KRATOS_ISOGEOMETRIC_APPLICATION_MULTIPATCH_REFINEMENT_UTILITY_H_INCLUDED

// System includes
#include <vector>

// External includes
#include <boost/array.hpp>

// Project includes
#include "includes/define.h"
#include "containers/array_1d.h"
#include "custom_utilities/bspline_utils.h"
#include "custom_utilities/nurbs/knot_array_1d.h"
#include "custom_utilities/control_point.h"
#include "custom_utilities/grid_function.h"
#include "custom_utilities/patch.h"
// #include "custom_utilities/hierarchical_bsplines/hb_mesh.h"

namespace Kratos
{

/**
Utility to control the refinement on multipatch structure
 */
class MultiPatchRefinementUtility
{
public:
    /// Pointer definition
    KRATOS_CLASS_POINTER_DEFINITION(MultiPatchRefinementUtility);

    /// Type definition
    typedef KnotArray1D<double> knot_container_t;
    typedef typename knot_container_t::knot_t knot_t;

    /// Default constructor
    MultiPatchRefinementUtility() {}

    /// Destructor
    virtual ~MultiPatchRefinementUtility() {}

    /*************************************************************************
                                    B-SPLINES
    *************************************************************************/

    /// Insert the knots to the NURBS patch and make it compatible across neighbors
    template<int TDim>
    void InsertKnots(typename Patch<TDim>::Pointer& pPatch, const std::vector<std::vector<double> >& ins_knots)
    {
        std::set<std::size_t> refined_patches;
        InsertKnots<TDim>(pPatch, refined_patches, ins_knots);
    }

    /// Insert the knots to the NURBS patch and make it compatible across neighbors
    template<int TDim>
    void InsertKnots(typename Patch<TDim>::Pointer& pPatch, std::set<std::size_t>& refined_patches, const std::vector<std::vector<double> >& ins_knots);

    /// Degree elevation for the NURBS patch and make it compatible across neighbors
    template<int TDim>
    void DegreeElevate(typename Patch<TDim>::Pointer& pPatch, const std::vector<std::size_t>& order_increment)
    {
        std::set<std::size_t> refined_patches;
        DegreeElevate<TDim>(pPatch, refined_patches, order_increment);
    }

    /// Degree elevation for the NURBS patch and make it compatible across neighbors
    template<int TDim>
    void DegreeElevate(typename Patch<TDim>::Pointer& pPatch, std::set<std::size_t>& refined_patches, const std::vector<std::size_t>& order_increment);

    /*************************************************************************
                              HIERARCHICAL B-SPLINES
    *************************************************************************/

    /// Information
    virtual void PrintInfo(std::ostream& rOStream) const
    {
        rOStream << "MultiPatchRefinementUtility";
    }

    virtual void PrintData(std::ostream& rOStream) const
    {
    }

private:

    /// Compute the transformation matrix for knot insertion (NURBS version)
    template<int TDim>
    void ComputeBsplinesKnotInsertionCoefficients(
        Matrix& T,
        std::vector<std::vector<double> >& new_knots,
        typename BSplinesFESpace<TDim>::Pointer& pFESpace,
        const std::vector<std::vector<double> >& ins_knots) const
    {
        std::stringstream ss;
        ss << __FUNCTION__ << " is not implemented for dimension " << TDim;
        KRATOS_THROW_ERROR(std::logic_error, ss.str(), "")
    }

    template<int TDim>
    void ComputeBsplinesDegreeElevation(
        const StructuredControlGrid<TDim, ControlPoint<double> >& ControlPoints,
        const BSplinesFESpace<TDim>& rFESpace,
        const std::vector<std::size_t>& order_increment,
        StructuredControlGrid<TDim, ControlPoint<double> >& NewControlPoints,
        std::vector<std::vector<double> >& new_knots) const
    {
        std::stringstream ss;
        ss << __FUNCTION__ << " is not implemented for dimension " << TDim;
        KRATOS_THROW_ERROR(std::logic_error, ss.str(), "")
    }

};

/// output stream function
inline std::ostream& operator <<(std::ostream& rOStream, const MultiPatchRefinementUtility& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);
    return rOStream;
}

} // namespace Kratos.

#include "multipatch_refinement_utility.hpp"

#endif // KRATOS_ISOGEOMETRIC_APPLICATION_MULTIPATCH_REFINEMENT_UTILITY_H_INCLUDED defined

