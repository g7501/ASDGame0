#include <chrono>
#include "GameInstance.h"
#include <stdlib.h>         




void GameInstance::GoldCalulation(double DeltaTime)
{
    if (SecondTimer<0)
    {
        SecondTimer = 1;
        //tc money
        Gold += 5*(1+Mines.size());
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
            if (CurrentPlaceObject!="")
            {
                
                if(CurrentPlaceObject=="StandardTower" && Gold>=100)
                {
                    Buildings.push_back(new Building(CurrentPlaceObject, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom-Camera::Location));
                    Gold -= 100;
                }
                if (CurrentPlaceObject == "Mine" && Gold >= 150)
                {
                    Mines.push_back(new Building(CurrentPlaceObject, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location));
                    Gold -= 150;
                }

                if (CurrentPlaceObject == "Mage" && Gold >= 150)
                {
                    Buildings.push_back(new Building(CurrentPlaceObject, (sf::Vector2f)sf::Mouse::getPosition() / Camera::Zoom - Camera::Location));
                    Gold -= 150;
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
    inst->AimingDirection = inst->FindLookAtVector(Nearest);




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
        if (Mines.size()>0)
        {
            inst->Target = Mines.at(rand()%Mines.size());
        }
        else
        {
            inst->Target = Town;
        }
    }

    if (inst->Name == "Knight")
    {
        //might want to make this a little more verbose
        if (Buildings.size() > 0)
        {
            inst->Target = Buildings.at(rand() % Buildings.size());
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
    


    if (Buildings.size()>4)
    {
        Soldiers.push_back(new Soldier("Grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
        Soldiers.push_back(new Soldier("Giant", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
        Soldiers.push_back(new Soldier("Giant", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
        Soldiers.push_back(new Soldier("Knight", sf::Vector2f(std::rand() % 3000 - 1500, std::rand() % 3000 - 1500), nullptr));
    }

    if (Mines.size()>3 || Gold>650)
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

    if (Mines.size()>6 && TotalTime>45)
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

    if(Buildings.size() > 8)
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
        }



        
        Camera::CameraMovement(DeltaTime);



        window->clear();
        //Render background
        TerrainData->RenderTerrain(window);

        //render buildings
        
        AimAtNearestEnemy(Town);
        Town->RenderEntity(window);
        Town->EntityLogic(DeltaTime, &Projectiles, Soldiers);
        if (Town->Health<=0)
        {
            //this is how you lose
            exit(0);
        }
        

        for (Building* i: Buildings)
        {
            AimAtNearestEnemy(i);
            i->EntityLogic(DeltaTime, &Projectiles, Soldiers);
            i->RenderEntity(window);
            if (i->Health<=0)
            {
                Building* tmp = i;
                i = nullptr;
                Buildings.erase(std::remove(Buildings.begin(), Buildings.end(), i), Buildings.end());
                delete tmp;
            }
           
        }
        for(Building* i: Mines)
        {
            i->RenderEntity(window);
        }



        //render enemies
        for(Soldier* i : Soldiers)
        {
            if (i->Target == nullptr)
            {
                //there is no target building so set it
                FindBuildingtoAttack(i);
            }
            i->EntityLogic(DeltaTime);
            i->RenderEntity(window);

        }
       
        

        for(Projectile* i: Projectiles)
        {
           
            i->EntityLogic(DeltaTime);
              
            
            i->RenderEntity(window);
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
            Projectiles.erase(std::remove(Projectiles.begin(), Projectiles.end(), i), Projectiles.end());
            delete tmp;
        }
        ProjectileRemovals.clear();



        //calculate money
        GoldCalulation(DeltaTime);
        //last to render is the UI
        

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
    Anim::LoadAllAnims();
    SoundData::LoadAllSounds();
   

    config = getConfiguration();
    TerrainData = new Terrain();

    window = new sf::RenderWindow(sf::VideoMode(config.ScreenX, config.ScreenY), "TD Game");
   



    Town = new TownCentre();
    //tmp
    Soldiers.push_back(new Soldier("Grunt",sf::Vector2f(500,300),Town));
    
    UI = new HUD();


   
    
    

}


