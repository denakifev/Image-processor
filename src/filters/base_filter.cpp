#include "base_filter.h"

namespace image_processor::filters {

BaseFilter::~BaseFilter(){};
void BaseFilter::Apply(Image& image) const {};

}  // namespace image_processor::filters
