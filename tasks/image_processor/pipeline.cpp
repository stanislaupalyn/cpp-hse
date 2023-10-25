#include "pipeline.h"

Pipeline::~Pipeline() {
    for (Filter* filter : filters_) {
        delete filter;
    }
}

void Pipeline::ApplyPipeline(BMP& bmp) {
    for (Filter* filter : filters_) {
        filter->Apply(bmp);
    }
}