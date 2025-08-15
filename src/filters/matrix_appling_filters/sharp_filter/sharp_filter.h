#pragma once

#include "../matrix_appling_filter.h"

namespace image_processor::filters {

class SharpFilter : public MatrixApplyingFilter {
protected:
    void SetMatrix() override;

public:
    SharpFilter();
    ~SharpFilter() override;
};

}  // namespace image_processor::filters