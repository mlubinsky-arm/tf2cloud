#include "model.h"
// #include "models/data.hpp" // uTensor

// run inference
float get_model_result(float* temp_value) {
    return 0.0f;
/*
    Context ctx;
    Tensor* temp_value_tensor = new WrappedRamTensor<float>({1,10}, (float*) &temp_value);
    get_data_ctx(ctx, temp_value_tensor);
    printf("...Running Eval...");
    ctx.eval();
    printf("finished....");
    S_TENSOR prediction = ctx.get({"dense_3_1/BiasAdd:0"});
    float result = *(prediction->read<float>(0,0));
    return result;
*/
}
