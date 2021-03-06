#ifndef TANH_H
#define TANH_H

#include "util/gnn_macros.h"
#include "nn/factor.h"
#include "nn/variable.h"

#include <memory>

namespace gnn
{

template<typename Dtype>
void TanhAct(DTensor<CPU, Dtype>& in, DTensor<CPU, Dtype>& out);

template<typename Dtype>
void TanhAct(DTensor<GPU, Dtype>& in, DTensor<GPU, Dtype>& out);

template<typename Dtype>
void TanhDeriv(DTensor<CPU, Dtype>& dst, DTensor<CPU, Dtype>& cur_output, DTensor<CPU, Dtype>& cur_grad);

template<typename Dtype>
void TanhDeriv(DTensor<GPU, Dtype>& dst, DTensor<GPU, Dtype>& cur_output, DTensor<GPU, Dtype>& cur_grad);

/**
 * @brief      the rectifer linear unit operator
 *
 * @tparam     mode   { CPU/GPU }
 * @tparam     Dtype  { float/double }
 */
template<typename mode, typename Dtype>
class Tanh: public Factor
{
public:
	static std::string StrType()
	{
		return "Tanh";
	}

	using OutType = std::shared_ptr< DTensorVar<mode, Dtype> >;
	
	/**
	 * @brief      Creates an out variable.
	 *
	 * @return     return a tensor with same shape/type as input tensor
	 */
	OutType CreateOutVar()
	{
		auto out_name = this->name + ":out_0";
		return std::make_shared< DTensorVar<mode, Dtype> >(out_name);
	}

	/**
	 * @brief      constructor
	 *
	 * @param[in]  _name     The name
	 * @param[in]  _properr  whether propagate error
	 */
	Tanh(std::string _name, PropErr _properr = PropErr::T);

	virtual void Forward(std::vector< std::shared_ptr<Variable> >& operands, 
						 std::vector< std::shared_ptr<Variable> >& outputs) override;

	virtual void Backward(std::vector< std::shared_ptr<Variable> >& operands, 
						  std::vector< bool >& isConst, 
						  std::vector< std::shared_ptr<Variable> >& outputs) override;	
};

}

#endif