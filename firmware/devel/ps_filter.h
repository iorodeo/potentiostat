#ifndef PS_FILTER_H
#define PS_FILTER_H

namespace ps 
{

    struct LowPassParam
    {
        float cutoffFreq;   //  cutoff frequency (-3dB) for fileter cascade 
        float initialValue;
        unsigned int order;
    };

    // Cascaded first order low-pass filters
    class LowPass
    {
        public:

            static const unsigned int MaxOrder_ = 5; 
            static const unsigned int MinOrder_ = 1;

            LowPass(float cutoff_freq=1.0, unsigned int order=1, float value=0.0);
            LowPass(LowPassParam param);

            void setParam(float cutoff_freq, unsigned int order, float value);
            void setParam(LowPassParam param);
            LowPassParam param();

            float cutoffFreq();
            void setCutoffFreq(float cutoffFreq);

            float initialValue();
            void setInitialValue(float initialValue);

            float order();
            void setOrder(unsigned int order);
            float singleStageRC();
            float singleStageCutoffFreq();

            void update(float value, float dt);
            void reset();
            float value() const;

        protected:

            LowPassParam param_;
            volatile float state_[MaxOrder_+1]; 
            float rc_;
            float elemCutoffFreq_;
            void initializeState();
    };

} // namespace filter

#endif


