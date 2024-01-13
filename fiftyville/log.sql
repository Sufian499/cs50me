-- Keep a log of any SQL queries you execute as you solve the mystery.
-- All you know is that the theft took place on July 28, 2023 and that it took place on Humphrey Street.
-- Catch the crime scene report by the date of the theft
SELECT *
  FROM crime_scene_reports AS csr
  WHERE csr.year = '2023'
  AND csr.month = '7'
  AND csr.day = '28'
  AND csr.street = 'Humphrey Street';
/*
Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery
*/
-- We know the theft took place at 10:15 in a bakery and whe have 3 witnesses that held an interview
SELECT i.name, i.transcript
  FROM interviews AS i
  WHERE i.year = '2023'
  AND i.month = '7'
  AND i.day = '28';
/*
| Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
*/
-- Dentro de los 10 minutos en el que se produjo el robo, el ladron se fue a un coche y se fue. time frame 10:15 - 10:25
-- El ladron antes de el robo en Leggett Street retiro dinero en el ATM
-- Cuando el ladron se estaba llendo de la panaderia hizo una llamada de menos de 1 minuto, diciendo que mañana (29) tomaría el vuelo más temprano fuera de Fiftyville y el complice sería quien compraría el ticket.

-- Quien se fue de la bakery a las 10
-- Matriculas de los coches que se fueron en el marco de tiempo y la gente con esas matriculas
SELECT bsl.id, bsl.hour, bsl.minute, bsl.activity, bsl.license_plate, p.name, p.phone_number, p.passport_number
  FROM bakery_security_logs as bsl
    JOIN people as p
      ON p.license_plate = bsl.license_plate
  WHERE bsl.year = '2023'
  AND bsl.month = '7'
  AND bsl.day = '28'
  AND bsl.hour = '10'
  AND bsl.minute <= '26'
  AND bsl.activity = 'exit';

-- Quienes retiraron dinero en el ATM de Leggett Street.
SELECT atm.id, atm.account_number, atm.amount, p.name, p.id, p.phone_number, p.license_plate
  FROM atm_transactions as atm
    JOIN people as p, bank_accounts as ba
      ON ba.account_number = atm.account_number AND p.id = ba.person_id
  WHERE atm.year = '2023'
  AND atm.month = '7'
  AND atm.day = '28'
  AND atm.transaction_type = 'withdraw'
  AND atm.atm_location = 'Leggett Street';

-- LLamadas y quien las hizo
SELECT pc.id, pc.caller, caller_person.name, pc.receiver, receiver_person.name, pc.duration
  FROM phone_calls as pc
    JOIN people as caller_person
      ON pc.caller = caller_person.phone_number
    JOIN people as receiver_person
      ON pc.receiver = receiver_person.phone_number
  WHERE pc.year = '2023'
  AND pc.month = '7'
  AND pc.day = '28'
  AND pc.duration <= 60;
-- Mirar los vuelos más temprano 1 día despues del robo
SELECT f.id, f.origin_airport_id, air_o.city, f.destination_airport_id, air_d.city, f.hour, f.minute
  FROM flights as f
    JOIN airports AS air_o
      ON f.origin_airport_id = air_o.id
    JOIN airports AS air_d
      ON f.destination_airport_id = air_d.id
  WHERE f.year = '2023'
  AND f.month = '7'
  AND f.day = '29'
  ORDER BY f.hour ASC, f.minute ASC
  LIMIT 1;
  -- NEW YORK!
-- Check passengers of the flight
SELECT pas.passport_number, pas.seat, p.name
  FROM passengers AS pas
    JOIN people as p
      ON pas.passport_number = p.passport_number
  WHERE pas.flight_id = 36;
 -- Merge all
SELECT p.name
  FROM people AS p
  WHERE p.phone_number IN (
      SELECT pc.caller
      FROM phone_calls as pc
      WHERE pc.year = '2023'
      AND pc.month = '7'
      AND pc.day = '28'
      AND pc.duration <= 60
  )
  AND p.passport_number IN (
    SELECT pas.passport_number
    FROM passengers AS pas
      JOIN people as p
        ON pas.passport_number = p.passport_number
    WHERE pas.flight_id = 36
  )
  AND p.license_plate IN (
    SELECT bsl.license_plate
    FROM bakery_security_logs as bsl
      JOIN people as p
        ON p.license_plate = bsl.license_plate
    WHERE bsl.year = '2023'
    AND bsl.month = '7'
    AND bsl.day = '28'
    AND bsl.hour = '10'
    AND bsl.minute <= '26'
    AND bsl.activity = 'exit'
  )
  AND p.id IN (
    SELECT  p.id
    FROM atm_transactions as atm
      JOIN people as p, bank_accounts as ba
        ON ba.account_number = atm.account_number AND p.id = ba.person_id
    WHERE atm.year = '2023'
    AND atm.month = '7'
    AND atm.day = '28'
    AND atm.transaction_type = 'withdraw'
    AND atm.atm_location = 'Leggett Street'
  );

-- Yeah is bruce
-- Who is the accomplice?
SELECT pc.caller, caller_person.name, pc.receiver, receiver_person.name
  FROM phone_calls as pc
    JOIN people as caller_person
      ON pc.caller = caller_person.phone_number and caller_person.name = 'Bruce'
    JOIN people as receiver_person
      ON pc.receiver = receiver_person.phone_number
  WHERE pc.year = '2023'
  AND pc.month = '7'
  AND pc.day = '28'
  AND pc.duration <= 60;
