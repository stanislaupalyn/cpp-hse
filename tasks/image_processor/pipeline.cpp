#include "pipeline.h"

Pipeline::~Pipeline() {
    for (Filter* filter : filters_) {
        delete filter;
    }
}

void Pipeline::ApplyPipeline(Image& image) {
    for (Filter* filter : filters_) {
        filter->Apply(image);
    }
}