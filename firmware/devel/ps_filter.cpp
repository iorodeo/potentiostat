#include "ps_filter.h"
#include <Arduino.h>

namespace ps 
{
    // Public methods
    // ------------------------------------------------------------------------
    LowPass::LowPass(float cutoffFreq,  unsigned int order, float value)
    {
        setParam(cutoffFreq, order, value);
        initializeState();
    }

    LowPass::LowPass(LowPassParam param)
    {
        setParam(param);
        initializeState();
    }

    void LowPass::setParam(float cutoffFreq, unsigned int order, float value)
    {
        param_.initialValue = value;
        param_.order = min(order,MaxOrder_);
        param_.order = max(param_.order,MinOrder_);
        setCutoffFreq(cutoffFreq);
    }

    void LowPass::setParam(LowPassParam param)
    {
        param_ = param;
        setCutoffFreq(param.cutoffFreq);
    }

    LowPassParam LowPass::param()
    {
        return param_;
    }

    float LowPass::cutoffFreq()
    {
        return param_.cutoffFreq;
    }

    void LowPass::setCutoffFreq(float cutoffFreq)
    {
        param_.cutoffFreq = cutoffFreq;
        float gainScale = 1.0/ (sqrt( pow(2.0, 1.0/float(param_.order)) - 1.0));
        elemCutoffFreq_ = param_.cutoffFreq*gainScale; // Cutoff freqency for first order stages
        rc_ = 1.0/(2.0*M_PI*elemCutoffFreq_);
    }


    float LowPass::initialValue()
    {
        return param_.initialValue;
    }

    void LowPass::setInitialValue(float initialValue)
    {
        param_.initialValue = initialValue;
    }

    float LowPass::order()
    {
        return param_.order;
    }

    void LowPass::setOrder(unsigned int order)
    {
        param_.order = order;
    }

    float LowPass::singleStageRC()
    {
        return rc_;
    }

    float LowPass::singleStageCutoffFreq()
    {
        return elemCutoffFreq_;
    }

    void LowPass::update(float value, float dt)
    {
        float alpha = dt/(rc_ + dt);
        state_[0] = value;
        for (unsigned int i=1; i<=param_.order; i++)
        {
            state_[i] = (1.0 - alpha)*state_[i] + alpha*state_[i-1]; 
        }
    }

    void LowPass::reset()
    {
        initializeState();
    }

    float LowPass::value() const
    {
        return state_[param_.order];
    }

    // Protected methods
    // ------------------------------------------------------------------------

    void LowPass::initializeState()
    {
        for (unsigned int i=0; i<MaxOrder_+1; i++)
        {
            state_[i] = param_.initialValue;
        }
    }
}
