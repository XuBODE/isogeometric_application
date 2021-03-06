//
//   Project Name:        Kratos
//   Last Modified by:    $Author: hbui $
//   Date:                $Date: 13 Nov 2017 $
//   Revision:            $Revision: 1.0 $
//
//

#if !defined(KRATOS_ISOGEOMETRIC_APPLICATION_ISOGEOMETRIC_UTILITY_H_INCLUDED)
#define  KRATOS_ISOGEOMETRIC_APPLICATION_ISOGEOMETRIC_UTILITY_H_INCLUDED

// System includes
#include <vector>
#include <fstream>

// External includes

// Project includes
#include "includes/define.h"
#include "includes/model_part.h"
#include "custom_utilities/grid_function.h"
#include "custom_utilities/patch.h"
#include "custom_utilities/patch_interface.h"
#include "custom_utilities/multipatch.h"

namespace Kratos
{

/**
 * Abstract class for all isogeometric utility.
 */
class IsogeometricUtility
{
public:
    /// Pointer definition
    KRATOS_CLASS_POINTER_DEFINITION(IsogeometricUtility);

    /// Type definition

    /// Default constructor
    IsogeometricUtility() {}

    /// Destructor
    virtual ~IsogeometricUtility() {}

    /// Get the last node id of the model part
    static std::size_t GetLastNodeId(ModelPart& r_model_part)
    {
        std::size_t lastNodeId = 0;
        for(typename ModelPart::NodesContainerType::iterator it = r_model_part.Nodes().begin();
                it != r_model_part.Nodes().end(); ++it)
        {
            if(it->Id() > lastNodeId)
                lastNodeId = it->Id();
        }

        return lastNodeId;
    }

    /// Get the last element id of the model part
    static std::size_t GetLastElementId(ModelPart& r_model_part)
    {
        std::size_t lastElementId = 0;
        for(typename ModelPart::ElementsContainerType::ptr_iterator it = r_model_part.Elements().ptr_begin();
                it != r_model_part.Elements().ptr_end(); ++it)
        {
            if((*it)->Id() > lastElementId)
                lastElementId = (*it)->Id();
        }

        return lastElementId;
    }

    /// Get the last condition id of the model part
    static std::size_t GetLastConditionId(ModelPart& r_model_part)
    {
        std::size_t lastCondId = 0;
        for(typename ModelPart::ConditionsContainerType::ptr_iterator it = r_model_part.Conditions().ptr_begin();
                it != r_model_part.Conditions().ptr_end(); ++it)
        {
            if((*it)->Id() > lastCondId)
                lastCondId = (*it)->Id();
        }

        return lastCondId;
    }

    /// Get the last properties id of the model_part
    static std::size_t GetLastPropertiesId(ModelPart& r_model_part)
    {
        std::size_t lastPropId = 0;
        for(typename ModelPart::PropertiesContainerType::ptr_iterator it = r_model_part.rProperties().ptr_begin();
                it != r_model_part.rProperties().ptr_end(); ++it)
        {
            if((*it)->Id() > lastPropId)
                lastPropId = (*it)->Id();
        }

        return lastPropId;
    }

    /// Find the element in the KRATOS container with specific key
    template<class TContainerType, class TKeyType>
    static typename TContainerType::iterator FindKey(TContainerType& ThisContainer , TKeyType ThisKey, std::string ComponentName)
    {
        typename TContainerType::iterator i_result;
        if((i_result = ThisContainer.find(ThisKey)) == ThisContainer.end())
        {
            std::stringstream buffer;
            buffer << ComponentName << " #" << ThisKey << " is not found.";
            KRATOS_THROW_ERROR(std::invalid_argument, buffer.str(), "");
        }

        return i_result;
    }

    /// Create a condition taking the same geometry as the parent element
    static Condition::Pointer CreateConditionFromElement(const std::string& sample_condition_name,
        std::size_t& lastConditionId, Element::Pointer pElement, Properties::Pointer pProperties )
    {
        Condition const& r_clone_condition = KratosComponents<Condition>::Get(sample_condition_name);

        // REMARK: when creating the condition here, the integration rule is not passed. Instead the default integration rule of this element_type is applied, which may be not the same as the original element.
        Condition::Pointer pNewCondition = r_clone_condition.Create(++lastConditionId, pElement->pGetGeometry(), pProperties);

        std::cout << "1 condition of type " << sample_condition_name << " is created" << std::endl;

        return pNewCondition;
    }

    /// List the nodes, elements, conditions of a model_part
    static void ListModelPart(ModelPart& r_model_part)
    {
        for(typename ModelPart::NodesContainerType::iterator it = r_model_part.Nodes().begin();
                it != r_model_part.Nodes().end(); ++it)
        {
            std::cout << "Node #" << it->Id() << ": ("
                      << it->X0() << ", " << it->Y0() << ", " << it->Z0() << ")" << std::endl;
        }

        for(typename ModelPart::ElementsContainerType::ptr_iterator it = r_model_part.Elements().ptr_begin();
                it != r_model_part.Elements().ptr_end(); ++it)
        {
            std::cout << typeid(*(*it)).name() << ": " << (*it)->Id() << std::endl;
        }

        for(typename ModelPart::ConditionsContainerType::ptr_iterator it = r_model_part.Conditions().ptr_begin();
                it != r_model_part.Conditions().ptr_end(); ++it)
        {
            std::cout << typeid(*(*it)).name() << ": " << (*it)->Id() << std::endl;
        }
    }

    /// Get the equation id of a dof associated with a node
    template<typename TVariableType>
    static std::size_t GetEquationId(ModelPart::NodeType& rNode, const TVariableType& rVariable)
    {
    	return rNode.GetDof(rVariable).EquationId();
    }

    /// Information
    template<class TClassType>
    static void PrintAddress(std::ostream& rOStream, typename TClassType::Pointer pInstance)
    {
        rOStream << pInstance << std::endl;
    }

    virtual void PrintInfo(std::ostream& rOStream) const
    {
        rOStream << "IsogeometricUtility";
    }

    virtual void PrintData(std::ostream& rOStream) const
    {
    }

}; // end class IsogeometricUtility


/// output stream function
inline std::ostream& operator <<(std::ostream& rOStream, const IsogeometricUtility& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);
    return rOStream;
}

} // namespace Kratos.

#endif // KRATOS_ISOGEOMETRIC_APPLICATION_ISOGEOMETRIC_UTILITY_H_INCLUDED defined

