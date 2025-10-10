#include "ModelController.hpp"

struct ModelController::Impl
{
    SearchResultModel searchResultModel;
    BackendsModel backendsModel;
};

ModelController::ModelController()
    : _impl{std::make_unique<Impl>()}
{
    SearchResultModel::registerType();
    BackendsModel::registerType();
}

ModelController::~ModelController()
{

}

SearchResultModel* ModelController::searchResultModel() const noexcept
{
    return &_impl->searchResultModel;
}

BackendsModel* ModelController::backendsModel() const noexcept
{
    return &_impl->backendsModel;
}

