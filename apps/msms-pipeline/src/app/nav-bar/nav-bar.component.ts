import { Component, OnInit } from '@angular/core';
import { AngularTokenService } from 'angular-token';

@Component({
  selector: 'cprobid-nav-bar',
  templateUrl: './nav-bar.component.html',
  styleUrls: ['./nav-bar.component.scss']
})
export class NavBarComponent implements OnInit {

  constructor(private tokenService: AngularTokenService) { }

  ngOnInit() {
  }

  get signedIn() {
    return this.tokenService.userSignedIn();
  }
}
