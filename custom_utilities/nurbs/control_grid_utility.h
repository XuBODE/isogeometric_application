//
//   Project Name:        Kratos
//   Last Modified by:    $Author: hbui $
//   Date:                $Date: 8 Nov 2017 $
//   Revision:            $Revision: 1.0 $
//
//

#if !defined(KRATOS_ISOGEOMETRIC_APPLICATION_CONTROL_GRID_UTILITY_H_INCLUDED)
#define  KRATOS_ISOGEOMETRIC_APPLICATION_CONTROL_GRID_UTILITY_H_INCLUDED

// System includes
#include <vector>

// External includes
#include <boost/array.hpp>

// Project includes
#include "includes/define.h"
#include "custom_utilities/nurbs/control_point.h"
#include "custom_utilities/nurbs/control_grid.h"

namespace Kratos
{

/**
This class is a library to generate various grid function for typical computational mechanics problems.
 */
class ControlGridUtility
{
public:
    /// Pointer definition
    KRATOS_CLASS_POINTER_DEFINITION(ControlGridUtility);

    /// Type definition
    typedef ControlPoint<double> ControlPointType;

    /// Default constructor
    ControlGridUtility() {}

    /// Destructor
    virtual ~ControlGridUtility() {}

    /// Generate the regular equidistant control point grid. All the point has unit weight.
    template<int TDim>
    static typename ControlGrid<ControlPointType>::Pointer CreateRegularControlPointGrid(
            const std::vector<double>& start, const std::vector<std::size_t>& ngrid, const std::vector<double>& spacing)
    {
        KRATOS_THROW_ERROR(std::logic_error, __FUNCTION__, "is not implemented")
    }

    /// Transform a grid function to new grid function by a matrix multiplication.
    template<typename TDataType, typename TMatrixType>
    static void Transform(const TMatrixType& TformMat,
            const ControlGrid<TDataType>& rControlGrid,
            ControlGrid<TDataType>& rNewControlGrid)
    {
        // ensure the transformation matrix size is compatible
        if (TformMat.size1() != rControlGrid.Size())
            KRATOS_THROW_ERROR(std::logic_error, "The first size of the transformation matrix is not compatible with old grid function size", "")

        if (TformMat.size2() != rNewControlGrid.Size())
            KRATOS_THROW_ERROR(std::logic_error, "The second size of the transformation matrix is not compatible with new grid function size", "")

        // get old data
        const typename ControlGrid<TDataType>::DataContainerType& OldData = rControlGrid.Data();

        // compute new data and store
        for (std::size_t i = 0; i < TformMat.size2(); ++i)
        {
            TDataType NewData(0.0);
            for (std::size_t j = 0; j < TformMat.size1(); ++j)
            {
                if (TformMat(j, i) != 0.0)
                    NewData += TformMat(j, i) * OldData[j];
            }
            rNewControlGrid.SetData(i, NewData);
        }
    }

    /// Information
    virtual void PrintInfo(std::ostream& rOStream) const
    {
        rOStream << "ControlGridUtility";
    }

    virtual void PrintData(std::ostream& rOStream) const
    {
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////

template<>
ControlGrid<ControlPoint<double> >::Pointer ControlGridUtility::CreateRegularControlPointGrid<1>(
        const std::vector<double>& start, const std::vector<std::size_t>& ngrid, const std::vector<double>& end)
{
    typename RegularControlGrid<1, ControlPointType>::Pointer pGrid
        = typename RegularControlGrid<1, ControlPointType>::Pointer(new RegularControlGrid<1, ControlPointType>(ngrid[0]));

    pGrid->SetName("CONTROL_POINT");

    std::vector<double> spacing = {(end[0] - start[0]) / (ngrid[0]-1),
                                (end[1] - start[1]) / (ngrid[0]-1),
                                (end[2] - start[2]) / (ngrid[0]-1)};

    for (std::size_t i = 0; i < ngrid[0]; ++i)
    {
        ControlPointType Point;
        Point.SetCoordinates(start[0] + i*spacing[0], start[1] + i*spacing[1], start[2] + i*spacing[2], 1.0);
        pGrid->SetValue(i, Point);
    }

    return pGrid;
}

template<>
ControlGrid<ControlPoint<double> >::Pointer ControlGridUtility::CreateRegularControlPointGrid<2>(
        const std::vector<double>& start, const std::vector<std::size_t>& ngrid, const std::vector<double>& end)
{
    typename RegularControlGrid<2, ControlPointType>::Pointer pGrid
        = typename RegularControlGrid<2, ControlPointType>::Pointer(new RegularControlGrid<2, ControlPointType>(ngrid[0], ngrid[1]));

    pGrid->SetName("CONTROL_POINT");

    std::vector<double> spacing = {(end[0] - start[0]) / (ngrid[0]-1), (end[1] - start[1]) / (ngrid[1]-1)};

    for (std::size_t i = 0; i < ngrid[0]; ++i)
    {
        for (std::size_t j = 0; j < ngrid[1]; ++j)
        {
            ControlPointType Point;
            Point.SetCoordinates(start[0] + i*spacing[0], start[1] + j*spacing[1], 0.0, 1.0);
            pGrid->SetValue(i, j, Point);
        }
    }

    return pGrid;
}

template<>
ControlGrid<ControlPoint<double> >::Pointer ControlGridUtility::CreateRegularControlPointGrid<3>(
        const std::vector<double>& start, const std::vector<std::size_t>& ngrid, const std::vector<double>& end)
{
    typename RegularControlGrid<3, ControlPointType>::Pointer pGrid
        = typename RegularControlGrid<3, ControlPointType>::Pointer(new RegularControlGrid<3, ControlPointType>(ngrid[0], ngrid[1], ngrid[2]));

    pGrid->SetName("CONTROL_POINT");

    std::vector<double> spacing = {(end[0] - start[0]) / (ngrid[0]-1),
                                (end[1] - start[1]) / (ngrid[1]-1),
                                (end[2] - start[2]) / (ngrid[2]-1)};

    for (std::size_t i = 0; i < ngrid[0]; ++i)
    {
        for (std::size_t j = 0; j < ngrid[1]; ++j)
        {
            for (std::size_t k = 0; k < ngrid[2]; ++k)
            {
                ControlPointType Point;
                Point.SetCoordinates(start[0] + i*spacing[0], start[1] + j*spacing[1], start[2] + k*spacing[2], 1.0);
                pGrid->SetValue(i, j, k, Point);
            }
        }
    }

    return pGrid;
}

/// output stream function
inline std::ostream& operator <<(std::ostream& rOStream, const ControlGridUtility& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);
    return rOStream;
}

} // namespace Kratos.

#endif // KRATOS_ISOGEOMETRIC_APPLICATION_CONTROL_GRID_UTILITY_H_INCLUDED defined
