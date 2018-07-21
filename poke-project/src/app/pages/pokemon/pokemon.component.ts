import { Component, OnInit } from '@angular/core';
import{ PokemonService } from '../../services/pokemon.service';

@Component({
  selector: 'app-pokemon',
  templateUrl: './pokemon.component.html',
  styleUrls: ['./pokemon.component.css']
})
export class PokemonComponent implements OnInit {

  constructor(public pkmnService: PokemonService){

  }

  ngOnInit() {
  }

}
