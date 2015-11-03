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
                    GeometryModel::result_type res;

                    GeometryModel::query()
                        .filter(std::string(name),orm::op::exact,GeometryModel::$name)
                        .get(res);

                    std::cout<<" - \""<<name<<"\" : ";
                    if(res.size() == 0)
                    {
                        std::cout<<"missing. Will be created"<<std::endl;
                        GeometryModel::type_ptr tmp = GeometryModel::create();
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
                    LayerTypeModel::result_type res;

                    LayerTypeModel::query()
                        .filter(std::string(name),orm::op::exact,LayerTypeModel::$name)
                        .get(res);

                    std::cout<<" - \""<<name<<"\" : ";
                    if(res.size() == 0)
                    {
                        std::cout<<"missing. Will be created"<<std::endl;
                        LayerTypeModel::type_ptr tmp = LayerTypeModel::create();
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

                MapModel::result_type res;
                MapModel::query()
                    .filter(std::string("default"),orm::op::exact,MapModel::$name)
                    .get(res);

                std::cout<<" - \"default\" : ";
                if(res.size() == 0)
                {
                    std::cout<<"missing. Will be created"<<std::endl;
                    MapModel::type_ptr tmp = MapModel::create();
                    tmp->name = "default";
                    tmp->geometry = GeometryModel::get(1);
                    tmp->scale = 50;
                    tmp->areaWidth = 10;
                    tmp->areaHeight = 10;
                    tmp->save();
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
