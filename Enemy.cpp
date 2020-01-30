/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 20:25:45 by jcruz-y-          #+#    #+#             */
/*   Updated: 2020/01/29 16:22:42 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Enemy.hpp"
#include "Bubble.hpp"
#include "BubbleEnemy.hpp"
#include "Game.hpp"

Shape Enemy::_shape(9, 3,
            std::string("    /    ") +
            std::string("}@@@@@>[>") +
            std::string("    \\    "));    

Enemy::Enemy(int x, int y, int velocity):
AObject(x, y, 1, 1, 50, 1, 'r'), _velocity(-velocity)
{
    this->_hp = _maxHp;
}

Enemy::~Enemy()
{
}

const Shape &Enemy::getShape() const
{
    return (_shape);
}

void Enemy::actionShoot(Game *g, const Keyboard &)
{
    this->_x += this->_velocity;

    if (g->getLevel() == 3)
    {
        int x = this->_x - 2;
        int y = this->_y +_shape.getSizeY()/2;
        BubbleEnemy *b = new BubbleEnemy(x, y, 2);
        g->addObject(b);
    }

}
void Enemy::actionMove(Game *, const Keyboard &)
{
    this->_x += this->_velocity;
}