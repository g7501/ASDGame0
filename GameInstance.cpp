#include <chrono>
#include "GameInstance.h"
#include <stdlib.h>         


void GameInstance::CameraMovement(double DeltaTime)
{
    CameraDelta = sf::Vector2f(0,0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        CameraDelta += sf::Vector2f(0, 400*DeltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        CameraDelta += sf::Vector2f(0, -400 * DeltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        CameraDelta += sf::Vector2f(400 * DeltaTime, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        CameraDelta += sf::Vector2f(-400 * DeltaTime, 0);
    }


    CameraLocation += CameraDelta;
}

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
                    Buildings.push_back(new Building(CurrentPlaceObject, (sf::Vector2f)sf::Mouse::getPosition()));
                    Gold -= 100;
                }
                if (CurrentPlaceObject == "Mine" && Gold >= 150)
                {
                    Mines.push_back(new Building(CurrentPlaceObject, (sf::Vector2f)sf::Mouse::getPosition()));
                    Gold -= 150;
                }

                if (CurrentPlaceObject == "Mage" && Gold >= 150)
                {
                    Buildings.push_back(new Building(CurrentPlaceObject, (sf::Vector2f)sf::Mouse::getPosition()));
                    Gold -= 150;
                }
            }
        }

    }
    else
    {
        MouseCooldown -= DeltaTime;
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
        if (i->DistanceTo(inst)<25)
        {
            
            i->Health -= inst->Damage;
           
            if (i->Health<=0)
            {


                Soldier* t1 = i;
                
                //cleanup
                Soldiers.erase(std::remove(Soldiers.begin(), Soldiers.end(), i), Soldiers.end());
                
                delete t1;
               
            }
            Projectile* t2 = inst;
            Projectiles.erase(std::remove(Projectiles.begin(), Projectiles.end(), inst), Projectiles.end());
            delete t2;

            return;
        }
    }
}

void GameInstance::SpawnEnemies()
{



    Soldiers.push_back(new Soldier("Soldiers/grunt", sf::Vector2f(std::rand()%2000-1000, std::rand() % 2000 - 1000), Town));
    Soldiers.push_back(new Soldier("Soldiers/grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
    Soldiers.push_back(new Soldier("Soldiers/grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));

    Soldiers.push_back(new Soldier("Soldiers/grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
    Soldiers.push_back(new Soldier("Soldiers/grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
    Soldiers.push_back(new Soldier("Soldiers/grunt", sf::Vector2f(std::rand() % 2000 - 1000, std::rand() % 2000 - 1000), Town));
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
            
        }



        
        CameraMovement(DeltaTime);



        window->clear();
        //Render background
        TerrainData->RenderTerrain(window, CameraDelta);

        //render buildings
        
        AimAtNearestEnemy(Town);
        Town->RenderEntity(window, CameraDelta);
        Town->EntityLogic(DeltaTime, &Projectiles, Soldiers);
        

        for (Building* i: Buildings)
        {
            AimAtNearestEnemy(i);
            i->EntityLogic(DeltaTime, &Projectiles, Soldiers);
            i->RenderEntity(window,CameraDelta);
           
        }
        for(Building* i: Mines)
        {
            i->RenderEntity(window,CameraDelta);
        }



        //render enemies
        for(Soldier* i : Soldiers)
        {
            
            i->EntityLogic(DeltaTime);
            i->RenderEntity(window, CameraDelta);
        }
       
        for(Projectile* i: Projectiles)
        {
            i->EntityLogic(DeltaTime);
            i->RenderEntity(window, CameraDelta);
            ProjectileCollision(i);
        }



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


        
        
    }

}




GameInstance::GameInstance()
{

    srand(std::time(0));
   //LoadAll anims
    Anim::LoadAllAnims();
   

    config = getConfiguration();
    TerrainData = new Terrain();

    window = new sf::RenderWindow(sf::VideoMode(config.ScreenX, config.ScreenY), "TD Game");
   



    Town = new TownCentre();
    //tmp
    Soldiers.push_back(new Soldier("Soldiers/grunt",sf::Vector2f(500,300),Town));
    
    UI = new HUD();


   
    
    

}


