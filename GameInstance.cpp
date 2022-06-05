#include <chrono>
#include "GameInstance.h"
#include <stdlib.h>








void GameInstance::GoldCalulation(double DeltaTime)
{
    if (SecondTimer<0)
    {
        SecondTimer = 1;
        //tc money
        Gold += 5*(1+ GameData::Mines.size());
    }
    else
    {
        SecondTimer -= DeltaTime;
    }


}

//These functions might have more stuff later
void GameInstance::SetObjectToTower()
{
    CurrentPlaceObject = "StandardTower";
}

void GameInstance::SetObjectToMine()
{
    CurrentPlaceObject = "Mine";
}

void GameInstance::SetObjectToMage()
{
    CurrentPlaceObject = "Mage";
}

//Also does the mouse
void GameInstance::HandleButtons(double DeltaTime)
{
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && MouseCooldown<=0)
    {
        MouseCooldown = 0.1;
        if (UI->StandardTowerButton.CallIfHovered())
        {
            SetObjectToTower();
           
        }
        else if (UI->MineButton.CallIfHovered())
        {
            SetObjectToMine();
        }
        else if (UI->MageButton.CallIfHovered())
        {
            SetObjectToMage();
        }
        else
        {

            //upgrade
            if ((Building::GetIndexOfHoveredTower(GameData::Buildings, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location))!=-1)
            {
                sf::Vector2i bLocT = (sf::Vector2i)GameData::Buildings.at(Building::GetIndexOfHoveredTower(GameData::Buildings, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location))->Loc;
               CurrentUpgrade = new FieldButton(bLocT,bLocT+sf::Vector2i(128,128), "UpgradeButton.png", 80);
            }



            else if (CurrentPlaceObject!="")
            {
                
                if(CurrentPlaceObject=="StandardTower")
                {
                    if (Gold >= 100 && Building::NotWithinBuilding(GameData::Buildings, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location))
                    {
                        GameData::Buildings.push_back(new Building(CurrentPlaceObject, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location));
                        Gold -= 100;
                        CurrentPlaceObject = "";
                    }
                    else
                    {
                        //play sound here
                    }

                }



                //can only build mines on dirt
                if (CurrentPlaceObject == "Mine")
                {
                    if (Gold >= 150 && Terrain::GetGroundTypeAtMouse() == GroundType::Dirt1 && Building::NotWithinBuilding(GameData::Buildings, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location))
                    {
                        GameData::Mines.push_back(new Building(CurrentPlaceObject, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location));
                        Gold -= 150;
                        CurrentPlaceObject = "";
                    }
                }

                if (CurrentPlaceObject == "Mage")
                {
                    if (Gold >= 150 && Building::NotWithinBuilding(GameData::Buildings, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location))
                    {
                        GameData::Buildings.push_back(new Building(CurrentPlaceObject, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location));
                        Gold -= 150;
                        CurrentPlaceObject = "";
                    }
                }
                
            }

        }

    }
    else
    {
        MouseCooldown -= DeltaTime * ! sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }


}

void GameInstance::AimAtNearestEnemy(Building* inst)
{
    //This is ran for each tower
    Soldier* Nearest = nullptr;
    float NearestDistance = std::numeric_limits<float>::max();
    for(Soldier* i: Soldiers)
    {
        if (inst->DistanceTo(i)<NearestDistance)
        {
            //maybe make this more efficient with branchless
            NearestDistance = inst->DistanceTo(i);
            Nearest = i;
        }
    }
    if (Nearest==nullptr)
    {
        inst->AimingDirection = sf::Vector2f(0,0);
        return;
    }
    if (inst->DistanceTo(Nearest)<inst->Range)
    {
        inst->AimingDirection = inst->FindLookAtVector(Nearest);
    }
    else
    {
        inst->AimingDirection = sf::Vector2f(0, 0);
    }


}

void GameInstance::ProjectileCollision(Projectile* inst)
{
    for(Soldier* i: Soldiers)
    {
        if (i->DistanceTo(inst)<25 && inst->Name=="Arrow" || i->DistanceTo(inst) < 55 && inst->Name == "Magic")
        {
            
            i->Health -= inst->Damage;
           
            if (i->Health<=0)
            {


                Soldier* t1 = i;
                
                //cleanup
                Soldiers.erase(std::remove(Soldiers.begin(), Soldiers.end(), i), Soldiers.end());
                
                delete t1;
               
            }

            ProjectileRemovals.push_back(inst);

            return;
        }
    }
}

void GameInstance::FindBuildingtoAttack(Soldier* inst)
{
    if (inst->Name=="Raider")
    {
        //might want to make this a little more verbose
        if (GameData::Mines.size()>0)
        {
            inst->Target = GameData::Mines.at(rand()% GameData::Mines.size());
        }
        else
        {
            inst->Target = Town;
        }
    }

    if (inst->Name == "Knight")
    {
        //might want to make this a little more verbose
        if (GameData::Buildings.size() > 0)
        {
            inst->Target = GameData::Buildings.at(rand() % GameData::Buildings.size());
        }
        else
        {
            inst->Target = Town;
        }
    }


}

void GameInstance::SpawnEnemies()
{
    Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand()%2000-1000, std::rand() % 2000 - 1000), Town));
    Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
    Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
    Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
    


    if (GameData::Buildings.size()>4)
    {
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
        Soldiers.push_back(new Soldier("Giant", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
        Soldiers.push_back(new Soldier("Giant", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
        Soldiers.push_back(new Soldier("Knight", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
    }

    if (GameData::Mines.size()>3 || Gold>650)
    {
        Soldiers.push_back(new Soldier("Raider", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Raider", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
    }

    if (TotalTime>15)
    {
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
    }

    if (TotalTime>60)
    {
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 4000 - 2000, std::rand() % 4000 - 2000), Town));
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 4000 - 2000, std::rand() % 4000 - 2000), Town));
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 4000 - 2000, std::rand() % 4000 - 2000), Town));
        Soldiers.push_back(new Soldier("Giant", sf::Vector2f(std::rand() % 4000 - 2000, std::rand() % 4000 - 2000), Town));
        Soldiers.push_back(new Soldier("Giant", sf::Vector2f(std::rand() % 4000 - 2000, std::rand() % 4000 - 2000), Town));
    }

    if (GameData::Mines.size()>6 && TotalTime>45)
    {
        Soldiers.push_back(new Soldier("Raider", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Raider", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Raider", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Raider", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Raider", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Raider", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
    }

    if (TotalTime>90)
    {
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 4000 - 2000, std::rand() % 4000 - 2000), Town));
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 4000 - 2000, std::rand() % 4000 - 2000), Town));
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 4000 - 2000, std::rand() % 4000 - 2000), Town));
        Soldiers.push_back(new Soldier("Raider", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Raider", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Knight", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
    }

    if(GameData::Buildings.size() > 8)
    {
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
        Soldiers.push_back(new Soldier("Giant", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
        Soldiers.push_back(new Soldier("Knight", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Knight", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Knight", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
        Soldiers.push_back(new Soldier("Knight", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
    }
    
}

void GameInstance::SaveGame()
{
    std::ofstream save("Save.cssave");
    save.write((char*)&TotalTime, 4);
    save.write((char*)&Gold,4);
    save.write((char*)&Camera::Location,8);
    save.write((char*)&Camera::Zoom, 4);
    save.write((char*)&Town->Health, 4);
    int tmp = GameData::Buildings.size();
    save.write((char*)&tmp,4);

    for(Building* i: GameData::Buildings)
    {
        save.write((char*)&i->Health,4);
        save.write((char*)&i->Loc.x,4);
        save.write((char*)&i->Loc.y, 4);
    }
    tmp = GameData::Mines.size();
    save.write((char*)&tmp, 4);
    for (Building* i : GameData::Mines)
    {
        save.write((char*)&i->Health, 4);
        save.write((char*)&i->Loc.x, 4);
        save.write((char*)&i->Loc.y, 4);
    }

    tmp = GameData::Soldiers.size();
    save.write((char*)&tmp, 4);
    for(Soldier* i: GameData::Soldiers)
    {
        save.write(i->Name.c_str(), i->Name.size());
        save.write((char*)& i->Health, 4);
        save.write((char*)& i->Loc, 8);
    }

    tmp = GameData::Projectiles.size();
    save.write((char*)&tmp, 4);
    for (Projectile* i: GameData::Projectiles)
    {
        save.write(i->Name.c_str(), i->Name.size());
        save.write((char*)&i->Loc,8);
        save.write((char*)&i->RemainingTime, 4);
        save.write((char*)&i->Attack, 4);
    }

    tmp = Entity::StaticEntities.size();
    save.write((char*)&tmp, 4);
    for (Entity* i : Entity::StaticEntities)
    {
        save.write(i->Name.c_str(), i->Name.size());
        save.write((char*)&i->Loc, 8);
        
    }





    save.close();
}

void GameInstance::GameLoop()
{
    sf::Event event;

    //time values
    double DeltaTime = 0;
    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;
    std::chrono::duration<double, std::milli> ms_double;

    while (window->isOpen())
    {
        //First thing is the deltatime

        t1 = std::chrono::high_resolution_clock::now();
        
        

        
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseWheelMoved)
            {
                Camera::Zoom += (float)event.mouseWheel.delta*0.1;
                if (Camera::Zoom<0.5)
                {
                    Camera::Zoom = 0.5;
                }
                if (Camera::Zoom>2)
                {
                    Camera::Zoom = 2;
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                //temp
                if (event.key.code == sf::Keyboard::Num1)
                {
                    SaveGame();
                }
            }
        }



        
        Camera::CameraMovement(DeltaTime);



        window->clear();
        //Render background
        TerrainData->RenderTerrain(window);

        //render buildings
        
        AimAtNearestEnemy(Town);
        Town->RenderEntity(window,DeltaTime);
        Town->EntityLogic(DeltaTime, &GameData::Projectiles, Soldiers);
        if (Town->Health<=0)
        {
            //this is how you lose
            exit(0);
        }
        

        for (Entity* i : Entity::StaticEntities)
        {
            if ((DecayEntity*)i)
            {
                DecayEntity* tmpDE = (DecayEntity*)i;
                tmpDE->RenderEntity(window, DeltaTime);
            }
            else
            {
                i->RenderEntity(window, DeltaTime);
            }
            
        }
        Entity::CleanStatics();


        for (Building* i: GameData::Buildings)
        {
            AimAtNearestEnemy(i);
            i->EntityLogic(DeltaTime, &GameData::Projectiles, Soldiers);
            i->RenderEntity(window, DeltaTime);
            if (i->Health<=0)
            {
                BuildingsRemovals.push_back(i);
                continue;
            }
           
        }
        for (Building* i : BuildingsRemovals)
        {
            Building* tmp = i;
            GameData::Buildings.erase(std::remove(GameData::Buildings.begin(), GameData::Buildings.end(), i), GameData::Buildings.end());
            delete tmp;
        }
        BuildingsRemovals.clear();

        for(Building* i: GameData::Mines)
        {
            i->RenderEntity(window, DeltaTime);
            if (i->Health <= 0)
            {
                MineRemovals.push_back(i);
                continue;
            }
        }

        for (Building* i: MineRemovals)
        {
            Building* tmp = i;
            GameData::Mines.erase(std::remove(GameData::Mines.begin(), GameData::Mines.end(), i), GameData::Mines.end());
            delete tmp;
        }
        MineRemovals.clear();

        //render enemies
        for(Soldier* i : Soldiers)
        {
            if (i->Target == nullptr)
            {
                //there is no target building so set it
                FindBuildingtoAttack(i);
            }
            i->EntityLogic(DeltaTime);
            i->RenderEntity(window, DeltaTime);

        }
       





        for(Projectile* i: GameData::Projectiles)
        {
           
            i->EntityLogic(DeltaTime);
              
            
            i->RenderEntity(window, DeltaTime);
            //might want to move this to own function
            if (i->RemainingTime < 0)//delete because old
            {
                ProjectileRemovals.push_back(i);
                continue;
            }
            ProjectileCollision(i);
            
 
        }

        for (Projectile* i: ProjectileRemovals)
        {
            Projectile* tmp = i;
            GameData::Projectiles.erase(std::remove(GameData::Projectiles.begin(), GameData::Projectiles.end(), i), GameData::Projectiles.end());
            delete tmp;
        }
        ProjectileRemovals.clear();





        //calculate money
        GoldCalulation(DeltaTime);
        //last to render is the UI
        
        if (CurrentUpgrade!=nullptr)
        {
            CurrentUpgrade->Render(window);
            
        }
        


        HandleButtons(DeltaTime);
        UI->Render(window, Gold);



        //spawn enemies
        if (EnemySpawnCountDown<=0)
        {
            SpawnEnemies();
            EnemySpawnCountDown = 6;
        }
        EnemySpawnCountDown -= DeltaTime;



        window->display();

        //last thing to do is find time
        t2 = std::chrono::high_resolution_clock::now();
        ms_double = t2 - t1;
        DeltaTime = ms_double.count() / 1000;
        TotalTime += DeltaTime;

        
        
    }

}

GameInstance::GameInstance()
{

    srand(std::time(0));
   //LoadAll anims

   

    config = getConfiguration();
    TerrainData = new Terrain();

    window = new sf::RenderWindow(sf::VideoMode(config.ScreenX, config.ScreenY), "TD Game");
   



    Town = new TownCentre();
    //tmp
    Soldiers.push_back(new Soldier("Grunt",sf::Vector2f(500,300),Town));
    
    UI = new HUD();


   
    
    

}