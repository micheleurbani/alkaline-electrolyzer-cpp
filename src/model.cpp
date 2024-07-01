//
// FMU4cpp Hello World example
//

#include <fmu4cpp/fmu_base.hpp>
#include <utility>
#include <iostream>
#include <cmath>


using namespace fmu4cpp;

class Model : public fmu_base {

public:
    Model(const std::string &instanceName, const std::string &resources)
        : fmu_base(instanceName, resources) {

        register_variable(
            real(
                "r1", [this] { return r1_; }, [this](double value) { r1_ = value; })
                .setCausality(causality_t::PARAMETER)
                .setVariability(variability_t::FIXED));

        register_variable(
            real(
                "r2", [this] { return r2_; }, [this](double value) { r2_ = value; })
                .setCausality(causality_t::PARAMETER)
                .setVariability(variability_t::FIXED));

        register_variable(
            real(
                "t1", [this] { return t1_; }, [this](double value) { t1_ = value; })
                .setCausality(causality_t::PARAMETER)
                .setVariability(variability_t::FIXED));

        register_variable(
            real(
                "t2", [this] { return t2_; }, [this](double value) { t2_ = value; })
                .setCausality(causality_t::PARAMETER)
                .setVariability(variability_t::FIXED));

        register_variable( real(
                "t3", [this] { return t3_; }, [this](double value) { t3_ = value; })
                .setCausality(causality_t::PARAMETER)
                .setVariability(variability_t::FIXED));

        register_variable( real(
                "Acell", [this] { return Acell_; }, [this](double value) { Acell_ = value; })
                .setCausality(causality_t::PARAMETER)
                .setVariability(variability_t::FIXED));

        register_variable( real(
                "Urev", [this] { return Urev_; }, [this](double value) { Urev_ = value; })
                .setCausality(causality_t::PARAMETER)
                .setVariability(variability_t::FIXED));

        register_variable( real(
                "Tel", [this] { return Tel_; }, [this](double value) { Tel_ = value; })
                .setCausality(causality_t::PARAMETER)
                .setVariability(variability_t::FIXED));

        register_variable( real(
                "s", [this] { return s_; }, [this](double value) { s_ = value; })
                .setCausality(causality_t::PARAMETER)
                .setVariability(variability_t::FIXED));

        register_variable(
            real(
                "I", [this] { return I_; }, [this](double value) { I_ = value; })
                .setCausality(causality_t::INPUT)
                .setVariability(variability_t::DISCRETE));

        register_variable(
            real(
                "U", [this] { return U_; })
                .setCausality(causality_t::OUTPUT)
                .setVariability(variability_t::DISCRETE)
                .setDependencies({get_real_variable("I")->index()}));

        Model::reset();
    }

    bool do_step(double currentTime, double dt) override {
        double r1 = get_real_variable("r1")->get();
        double r2 = get_real_variable("r2")->get();
        double t1 = get_real_variable("t1")->get();
        double t2 = get_real_variable("t2")->get();
        double t3 = get_real_variable("t3")->get();
        double Acell = get_real_variable("Acell")->get();
        double Urev = get_real_variable("Urev")->get();
        double Tel = get_real_variable("Tel")->get();
        double s = get_real_variable("s")->get();
        double I = get_real_variable("I")->get();

        double U = Urev + (r1 + r2 * Tel) / Acell * I + s * std::log((t1 + t2 / Tel + t3 / std::pow(Tel, 2)) / Acell * I + 1);
        std::cout << "U: " << U << std::endl;
        get_real_variable("U")->set(U);
        return true;
    }

    void reset() override {
        r1_     = 2.031208241179847e-05;
        r2_     = 1.274797205640144e-08;
        t1_     = 1.9889752425169336;
        t2_     = 2.370768719711065;
        t3_     = 16.874083460526798;
        s_      = 0.041119229477905195;
        Acell_  = 0.6;
        Urev_   = 1.2281701818935586;
        Tel_    = 88;
        I_      = 0.0;
        U_      = 0.0;
    }

private:
    double r1_;
    double r2_;
    double t1_;
    double t2_;
    double t3_;
    double Acell_;
    double Urev_;
    double Tel_;
    double s_;
    double I_;
    double U_;
};

model_info fmu4cpp::get_model_info() {
    model_info info;
    info.modelName = "Alkaline_Electrolyzer";
    info.description = "A simple alkaline electrolyzer model.";
    info.modelIdentifier = FMU4CPP_MODEL_IDENTIFIER;
    return info;
}

std::unique_ptr<fmu_base> fmu4cpp::createInstance(const std::string &instanceName, const std::string &fmuResourceLocation) {
    return std::make_unique<Model>(instanceName, fmuResourceLocation);
}
