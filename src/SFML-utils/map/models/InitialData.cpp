#include <SFML-utils/map/Models.hpp>

#include <ORM/backends/op.hpp>


namespace sfutils
{
    namespace map
    {

        bool loadInitialData()
        {
            std::cout<<"==== Database will be populate if nedeed ===="<<std::endl;

            {
                std::cout<<"== Checking GeometryModel =="<<std::endl;

                for(auto& name :  {"Hexa","HexaIso","Square","SquareIso","SquareStaggered","SquareIsoStaggered"})
                {
                    GeometryModel::pointer_array res;

                    GeometryModel::query()
                        .filter(std::string(name),orm::op::exact,GeometryModel::$name)
                        .get(res);

                    std::cout<<" - \""<<name<<"\" : ";
                    if(res.size() == 0)
                    {
                        std::cout<<"missing. Will be created"<<std::endl;
                        GeometryModel::pointer tmp = GeometryModel::create();
                        tmp->name = name;
                        tmp->save();

                    }
                    else
                    {
                        std::cout<<"OK"<<std::endl;
                    }
                }
            }

            {
                std::cout<<"== Checking LayerTypeModel =="<<std::endl;

                for(auto& name : {"tile", "sprite", "sprite_ptr","entity"})
                {
                    LayerTypeModel::pointer_array res;

                    LayerTypeModel::query()
                        .filter(std::string(name),orm::op::exact,LayerTypeModel::$name)
                        .get(res);

                    std::cout<<" - \""<<name<<"\" : ";
                    if(res.size() == 0)
                    {
                        std::cout<<"missing. Will be created"<<std::endl;
                        LayerTypeModel::pointer tmp = LayerTypeModel::create();
                        tmp->name = name;
                        tmp->save();

                    }
                    else
                    {
                        std::cout<<"OK"<<std::endl;
                    }
                }

            }

            {
                std::cout<<"== Cheching MapModel =="<<std::endl;

                MapModel::pointer_array res;
                MapModel::query()
                    .filter(std::string("default"),orm::op::exact,MapModel::$name)
                    .get(res);

                std::cout<<" - \"default\" : ";
                if(res.size() == 0)
                {
                    std::cout<<"missing. Will be created"<<std::endl;
                    MapModel::pointer tmp = MapModel::create();
                    tmp->name = "default";
                    tmp->geometry = GeometryModel::get(1);
                    tmp->scale = 50;
                    tmp->areaWidth = 10;
                    tmp->areaHeight = 10;
                    tmp->save();

                    LayerTypeModel::pointer_array models;
                    LayerTypeModel::query()
                        .filter(std::string("tile"),orm::op::exact,LayerTypeModel::$name)
                        .get(models);

                    LayerModel::pointer tmpLayer = LayerModel::create();
                    tmpLayer->name = "default";
                    tmpLayer->zBuffer = 1;
                    tmpLayer->isStatic = true;
                    tmpLayer->type = models[0];
                    tmpLayer->map = tmp;

                    tmpLayer->save();

                }
                else
                {
                    std::cout<<"OK"<<std::endl;
                }
            }

            std::cout<<"==== Database is OK ===="<<std::endl;

            return false;

        }
    }
}
