#include <iostream>
#include "application.h"

// ./image_processor input.txt output.txt -crop 800 600 -gs -blur 0.5

int main(int argc, char* argv[]) {
    Application app;
    app.Config();
    app.Start(argc, argv);
    return 0;
}


/*
CommandLineParser p;
p.Parse(argc, argv) -> ApplicationSettings

Application Settings
{
    vector<FilterSettings>
    {
        string name;
        vector<string> arguments;
    }
}


class Filter {
    interface

    virtual ApplyFilter() {

    }
    ...
}

class Blur : public Filter {

} .. class Crop : public Filer ...

vector<Filter*> pipeline;

// function pointer
typedef (Filter*)(*FilterProdPtr)(const FilterSettings&);
using FilterProdPtr = (Filter*)(*)(const FilterSettings&);

FilterProdPtr blurfp = &BlurProduce;

class FilterProducer {
    map<string, FilterProdPtr> filterProds;

    void AddProducer() {

    }

    FulterProdPtr GetProducer() {
        // return nullptr if not present
    }

    virtual Filter* Produce(FilterSettings ) {
        ...
    }
};

Class Pipeline {
    vector<Filter*> filters;

    void AddFilter() {

    }
    void Apply(BMP ) {

    }

    ~Pipeline() {
        // delete filters
    }
}.

for (FilterSettings& fs : ApplicationSettigs.filtres) {
    FilterProdPtr fprod = filFact.getProducer(fs.name);
    if (!fprod) {
        return FilterCreateResult::NotFound;
    }
    Filter* new_filter = frpod(fs);
    if (!new_filter) {
        return FilterCreateResult::NotFound;
    }
    pipeline.AddFilter(new_filter);
}

ParserCommandLine -> CreateFilerPipeline -> LoadBMP -> ApplyPipeline -> SaveBMP


class Application {
private:
    CommandLineParser
    FilterFactory ff;

    void Config() {
        ff.addProducer();
    }

    Application start() { // real main  
        try {

        } catch(bad filter arguments)
    }

};

// #include "blur_filter.h"
// #include "blur_filter_producer.h"

main () {
    try {
        Application app;
        app.Config();
        app.Start(argc, argv);
    } catch(std::exception) {
        cerr << "";
    } catch(...) {
        cerr << "unhandled exception code";
    }
}

*/