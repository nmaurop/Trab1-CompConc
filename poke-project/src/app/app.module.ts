import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { MaterializeModule } from 'angular2-materialize';

import { AppComponent } from './app.component';
import { NavbarComponent } from './navbar/navbar.component';
import { HomeComponent } from './pages/home/home.component';
import { PokemonComponent } from './pages/pokemon/pokemon.component';
import { BerriesComponent } from './pages/berries/berries.component';
import { AppRoutingModule } from './app.routing.module';
import{ HttpClientModule } from '@angular/common/http';
import{ PokemonService } from './services/pokemon.service';

@NgModule({
  declarations: [
    AppComponent,
    NavbarComponent,
    HomeComponent,
    PokemonComponent,
    BerriesComponent
  ],
  imports: [
    BrowserModule,
    MaterializeModule,
    AppRoutingModule,
    HttpClientModule
  ],
  providers: [
    PokemonService
    ],
  bootstrap: [AppComponent]
})
export class AppModule { }
