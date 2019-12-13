import { AccountService } from './../account.service';
import { Component, OnInit } from '@angular/core';


@Component({
  selector: 'cprobid-nav-bar',
  templateUrl: './nav-bar.component.html',
  styleUrls: ['./nav-bar.component.scss']
})
export class NavBarComponent implements OnInit {

  constructor(private account: AccountService) { }

  ngOnInit() {
  }

  get signedIn() {
    return this.account.userSignedIn();
  }
}
