//
// Created by matt on 4/30/18.
//

#ifndef GALAGA_HEALTH_H
#define GALAGA_HEALTH_H

class Health
{
public:
    explicit Health(int maxHp);

    int get() const;

    void reset();
    void takeDamage(int dmg);


private:
    int m_hp;
    int m_maxHp;
};

#endif //GALAGA_HEALTH_H
