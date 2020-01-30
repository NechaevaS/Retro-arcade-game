/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 20:25:45 by jcruz-y-          #+#    #+#             */
/*   Updated: 2020/01/29 12:13:14 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H
#include <iostream>
#include <string>
#include <ncurses.h>
#include "AObject.hpp"
#include "Shape.hpp"
#include <string>


class Enemy : public AObject
{

public:

    Enemy( void );               // default constructor
    Enemy( int const n );        // 
   
    ~Enemy( void );

    Enemy(int x, int y, int velocity);
    const Shape &getShape() const;
    void actionMove(Game *g, const Keyboard &k);
    void actionShoot(Game *g, const Keyboard &k); 

private:
    int _velocity;  
    static Shape _shape;
    Enemy( Enemy const &src ); // copy constructor, taking as a param 
                                  // instance of this class and making a copy
   // Enemy &operator=(const Enemy &)
    Enemy &operator=( const Enemy &rhs ); // Operator overload to update the
                                              // current instance (make assignments
                                              // of this class

};

#endif